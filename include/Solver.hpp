#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
using namespace std;

class Solver 
{
public:
    Solver();
    Solver(vector<double> &dx, vector<double> &Dx, vector<double> &ud, 
          vector<double> &d, vector<double> &ld, vector<double> &r, double omega, double k, 
          double N, double Sp, double Sc, 
          vector<double> &phi, vector<double> &gamma, double h,
          double T_inf, double T_b, double A);
    virtual ~Solver();
    virtual vector<double> Solve();
    virtual bool CheckConvergence();
    virtual void ComputeGamma(vector<double> &gamma, vector<double> &phi,
                             double omega, double k, double T_inf, double T_b);
protected:
    double omega, k, N, Sp, Sc, h, T_inf, T_b, A;
    unsigned const int MAXITER = 10000;
    const double TOL = 1E-10;
    vector<double> dx, Dx, ud, d, ld, r, phi, gamma;
    bool converged = false;
};

#endif