#ifndef NONLINEARFVM_H
#define NONLINEARFVM_H

#include "FVM.hpp"

class NonLinearFVM : public FVM
{
public:
    NonLinearFVM();
    NonLinearFVM (int N, double Sp, double Sc, double h, double T_inf, double T_b, double A);
    virtual ~NonLinearFVM();
    virtual void Assemble (vector<double> &ud, vector<double> &d, 
                          vector<double> &ld, vector<double> &phi, 
                          vector<double> &r, vector<double> &dx,
                          vector<double> &Dx, vector<double> &gamma, double omega, double k);
    virtual double dAldTp(double k, double omega, double kl, double kp, double dx, double Tp);
};

#endif