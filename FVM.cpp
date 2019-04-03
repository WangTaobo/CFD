#include "FVM.h"
#include <iostream>
FVM::FVM()
{
}

FVM::FVM(int N, double h, double P, double k, double A, double T_inf, double T_b)
{
    this->Sp = h * P / A;
    this->Sc = h * P * T_inf / A;
    this->N = N;
    this->h = h;
    this->gamma = k;
    this->T_inf = T_inf;
    this->T_b = T_b;
}

FVM::~FVM()
{
}

void FVM::Assemble(double* ud, double* d, double* ld, double* x, double* dx, double* Dx)
{
    for (auto i = 0; i < N - 1; i++)
    {
        ld[i] = gamma / dx[i]; // matrix indices [2 + i, 1 + i]
        ud[i] = gamma / dx[i]; // matrix indices [1 + i , 2 + 1]
        d[i] += - ud[i];
        d[i + 1] += -ld[i];
    }

    for (auto i = 0; i < N; i++)
    {
        d[i] += - Sp * Dx[i];
        x[i] = - Sc * Dx[i];
    }

    // Apply boundary conditions
    d[0] = 1; // left boundary
    ud[0] = 0; // left boundary
    x[0] = T_b; // left boundary
    
    d[N - 1] += -h; // right boundary
    x[N - 1] += -h * T_inf; // right boundary (Method A)
}