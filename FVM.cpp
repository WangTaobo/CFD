#include "FVM.h"

FVM::FVM(double k1, double k2, double k3, double k4, double k5, 
        double k6, double L, double L1, double L2, double L3, 
        double L4, double L5, double L6)
{
    this->k1 = k1;
    this->k2 = k2;
    this->k3 = k3;
    this->k4 = k4;
    this->k5 = k5;
    this->k6 = k6;
    this->L = L;
    this->L1 = L1;
    this->L2 = L2;
    this->L3 = L3;
    this->L4 = L4;
    this->L5 = L5;
    this->L6 = L6;
}

FVM::~FVM()
{
}

void FVM::Assemble(double* ud, double* d, double* ld, double* x)
{
    d[0] = k1+k2;
    d[1] = k2+k3;
    d[2] = k3+k4;
    d[3] = k4+k5;
    d[4] = k5+k6;    

    ld[0] = -k2;
    ld[1] = -k3;
    ld[2] = -k4;
    ld[3] = -k5;
    
    ud[0] = -k2;
    ud[1] = -k3;
    ud[2] = -k4;
    ud[3] = -k5;

    x[0] = k1*L1 - k2*L2;
    x[1] = k2*L2 - k3*L3;
    x[2] = k3*L3 - k4*L4;
    x[3] = k4*L4 - k5*L5;
    x[4] = k5*L5 + k6*L - k6*L6;
}