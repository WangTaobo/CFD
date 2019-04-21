#include "FVM.h"
#include <iostream>
FVM::FVM()
{
}

FVM::FVM(int N, double Sp, double Sc, double gamma, double h, double T_inf, double T_b)
{
    this->Sp = Sp;
    this->Sc = Sc;
    this->N = N;
    this->h = h;
    this->gamma = gamma;
    this->T_inf = T_inf;
    this->phib = T_b;
}

FVM::~FVM()
{
}

void FVM::Assemble(vector<double> &ud, vector<double> &d, 
vector<double> &ld, vector<double> &r, vector<double> &dx, vector<double> &Dx)
{
    for (auto i = 0; i < ld.size(); i++)
    {
        ld[i] -= gamma / dx[i]; // matrix indices [2 + i, 1 + i]
        ud[i] -= gamma / dx[i]; // matrix indices [1 + i , 2 + 1]
        d[i] -= ud[i];
        d[i + 1] -= ld[i];
    }

    for (auto i = 0; i < d.size(); i++)
    {
        d[i] -= Sp * Dx[i];
        r[i] = Sc * Dx[i];
    }

    // Apply boundary conditions
    d[0] = 1; // left boundary
    ud[0] = 0; // left boundary
    r[0] = phib; // left boundary
    
    d.back() += h; // right boundary
    r.back() += h * T_inf; // right boundary (Method A)
}