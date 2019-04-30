#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include "Solver.hpp"

class NewtonRaphson : public Solver
{
public:
    NewtonRaphson();
    NewtonRaphson(vector<double> &dx, vector<double> &Dx, vector<double> &ud, 
          vector<double> &d, vector<double> &ld, vector<double> &r, double omega, double k, 
          double N, double Sp, double Sc, 
          vector<double> &phi, vector<double> &gamma, double h,
          double T_inf, double T_b, double A);
    virtual ~NewtonRaphson();
    virtual void UpdatePhi(vector<double> &phi, vector<double> &deltaPhi);
    virtual vector<double> Solve();
    virtual bool CheckConvergence(vector<double> &old_phi, vector<double> &phi);
//    virtual bool CheckConvergence(vector<double> &r);

};

#endif