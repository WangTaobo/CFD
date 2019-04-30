#include "Picard.hpp"
#include "FVM.hpp"
#include "TDMA.hpp"
#include <iostream>
#include <cmath>

Picard::Picard() 
{
}

Picard::Picard(vector<double> &dx, vector<double> &Dx, vector<double> &ud, 
          vector<double> &d, vector<double> &ld, vector<double> &r, double omega, double k, 
          double N, double Sp, double Sc, 
          vector<double> &phi, vector<double> &gamma, double h,
          double T_inf, double T_b, double A)
            :Solver(dx, Dx, ud, d, ld, r, omega, k, N, Sp, Sc, phi, gamma, h, T_inf, T_b, A) 
{
}

Picard::~Picard() 
{
}

vector<double> Picard::Solve()
{
    FVM* fvm = new FVM(N, Sp, Sc, h, T_inf, T_b, A);
    TDMA* linearSolver = new TDMA(N);
    vector<double> old_phi(N, 0.0);

    for(unsigned iter; iter < MAXITER; iter++)
    {
        ComputeGamma(gamma, phi, omega, k, T_inf, T_b);
        fvm->Assemble(ud, d, ld, r, dx, Dx, gamma);
        linearSolver->LinSolve(ud, d, ld, phi, r);
        
        converged = CheckConvergence(old_phi, phi);
        if(converged) 
        {
            cout << "Number of Picard iterations " << ++iter << endl;
            return phi;
        }

        old_phi = phi;
    }    
}

bool Picard::CheckConvergence(vector<double> &old_phi, vector<double> &phi)
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