#include "Solver.hpp"
#include <cmath>

Solver::Solver() 
{
}

Solver::Solver(vector<double> &dx, vector<double> &Dx, vector<double> &ud, 
          vector<double> &d, vector<double> &ld, vector<double> &r, double omega, double k, 
          double N, double Sp, double Sc, 
          vector<double> &phi, vector<double> &gamma, double h,
          double T_inf, double T_b, double A)
{
    this->dx = dx;
    this->Dx = Dx;
    this->ud = ud;
    this->d = d;
    this->ld = ld;
    this->r = r;
    this->omega = omega;
    this->k = k;
    this->N = N,
    this->Sp = Sp;
    this->Sc = Sc;
    this->phi = phi;
    this->h = h;
    this->T_inf = T_inf;
    this->T_b = T_b;
    this->A = A;
    this->gamma = gamma;
}

Solver::~Solver() 
{
}

void Solver::ComputeGamma(vector<double> &gamma, vector<double> &phi,
                         double omega, double k, double T_inf, double T_b)
{   
    for(unsigned int i = 0; i < gamma.size(); i++)
    {
        gamma[i] = k*(1 + omega*pow( (phi[i] - T_inf) / (T_b - T_inf) , 3));
    }
}

bool Solver::CheckConvergence()
{
}

vector<double> Solver::Solve()
{
}