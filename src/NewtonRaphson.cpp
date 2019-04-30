#include "NewtonRaphson.hpp"
#include "mathlib.hpp"
#include "NonLinearFVM.hpp"
#include "TDMA.hpp"
#include <iostream>

NewtonRaphson::NewtonRaphson() 
{
}

NewtonRaphson::NewtonRaphson(vector<double> &dx, vector<double> &Dx, vector<double> &ud, 
          vector<double> &d, vector<double> &ld, vector<double> &r, double omega, double k, 
          double N, double Sp, double Sc, 
          vector<double> &phi, vector<double> &gamma, double h,
          double T_inf, double T_b, double A) 
          : Solver(dx, Dx, ud, d, ld, r, omega, k, N, Sp, Sc, phi, gamma, h, T_inf, T_b, A)
{
}

NewtonRaphson::~NewtonRaphson() 
{
}

void NewtonRaphson::UpdatePhi(vector<double> &phi, vector<double> &deltaPhi)
{
    for(unsigned int i = 0; i < phi.size(); i++)
    {
        phi[i] += deltaPhi[i];
    }
}

vector<double> NewtonRaphson::Solve()
{
    NonLinearFVM* fvm = new NonLinearFVM(N, Sp, Sc, h, T_inf, T_b, A);
    TDMA* linearSolver = new TDMA(N);
    
    vector<double> deltaPhi(N, 0.0);
    vector<double> oldPhi(N, 0.0);

    unsigned int iter = 0;
    
    for(iter; iter < MAXITER + 1; iter++)
    {
        ComputeGamma(gamma, phi, omega, k, T_inf, T_b);
        fvm->Assemble(ud, d, ld, phi, r, dx, Dx, gamma, omega, k);
        converged = CheckConvergence(oldPhi, phi);
        
        if(converged) 
        {
            cout << "Number of Newton iterations " << ++iter << endl;
            return phi;
        }

        linearSolver->LinSolve(ud, d, ld, deltaPhi, r);
        oldPhi = phi;
        UpdatePhi(phi, deltaPhi);
    }

    if (iter >= MAXITER)
    {
        cout << "Not converged !" << endl;
        throw false;
    }
}

/*bool NewtonRaphson::CheckConvergence(vector<double> &r)
{
    mathlib* n = new mathlib();
    double normRes = n->Norm(r.size(), r);
    if (normRes > TOL) 
        return false;
    return true;
}*/
bool NewtonRaphson::CheckConvergence(vector<double> &old_phi, vector<double> &phi)
{
    double err = 0.0;
    for(unsigned int i = 0; i < phi.size(); i++)
    {
        err += (pow( (phi[i] - old_phi[i]) / phi[i] , 2));
    }
    if (sqrt(err) > TOL )   
        return false;
    return true;
}