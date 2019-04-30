#ifndef PICARD_H
#define PICARD_H

#include "Solver.hpp"
#include <vector>

using namespace std;

class Picard : public Solver
{
public:
    Picard();
    Picard(vector<double> &dx, vector<double> &Dx, vector<double> &ud, 
          vector<double> &d, vector<double> &ld, vector<double> &r, double omega, double k, 
          double N, double Sp, double Sc, 
          vector<double> &phi, vector<double> &gamma, double h,
          double T_inf, double T_b, double A);
    virtual ~Picard();
    virtual vector<double> Solve();
    virtual bool CheckConvergence(vector<double> &old_phi, vector<double> &phi);
};

#endif