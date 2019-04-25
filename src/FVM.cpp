/*
This method mounts the matrix A = |D0 B0  0  0 ... ...   0|
                                  |A0 D1 B1  0 ... ...   0|
                                  |0  A1 D2 B2 ... ...   0|
                                  |... ... ... ... ...   0|
                                  |...A(N-2) D(N-1) B(N-1)|
                                  |0  0 ... 0  A(N-1) D(N)|, where
                                  B = UD and A = LD.
And vector r.
*/

#include "FVM.hpp"
#include <iostream>
FVM::FVM()
{
}

FVM::FVM(int N, double Sp, double Sc, double h, double T_inf, double T_b, double A)
{
    this->Sp = Sp;
    this->Sc = Sc;
    this->N = N;
    this->h = h;
    this->T_inf = T_inf;
    this->phib = T_b;
    this->A = A;
}

FVM::~FVM()
{
}

void FVM::Assemble(vector<double> &ud, vector<double> &d, 
                  vector<double> &ld, vector<double> &r, 
                  vector<double> &dx, vector<double> &Dx, 
                  vector<double> &gamma)
{
    double gamma_l;
    
    fill(ld.begin(), ld.end(), 0.0);
    fill(ud.begin(), ud.end(), 0.0);
    fill(d.begin(), d.end(), 0.0);
    fill(r.begin(), r.end(), 0.0);

    for (unsigned int i = 0; i < ld.size(); i++)
    {
        gamma_l = 2*gamma[i]*gamma[i + 1] / (gamma[i] + gamma[i + 1]);
        ld[i] -= A * gamma_l / dx[i]; // A * gamma_w / dx_w
        ud[i] -= A * gamma_l / dx[i]; // A * gamma_e / dx_e
        d[i] -= ud[i];
        d[i + 1] -= ld[i];
    }

    for (unsigned int i = 0; i < d.size(); i++)
    {
        d[i] -= A * Sp * Dx[i];
        r[i] = A * Sc * Dx[i];
    }

    // Apply boundary conditions
    d[0] = 1; // left boundary
    ud[0] = 0; // left boundary
    r[0] = phib; // left boundary
    
    d.back() += A * h; // right boundary
    r.back() += A * h * T_inf; // right boundary (Method A)
}