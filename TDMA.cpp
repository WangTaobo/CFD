#include "TDMA.h"

TDMA::TDMA()
{    
}

TDMA::TDMA(int N)
{    
    this->N = N;
}

TDMA::~TDMA () 
{
}

void TDMA::Solve (double* ud, double* d, double* ld, double* x)
{
    for (auto i = 1; i < N; i++) 
    {
        m = ld[i -1] / d[i - 1];
        d[i] -= m*ud[i - 1];
        x[i] -= m*x[i - 1];
    }

    x[N - 1] = x[N - 1] / d[N - 1];

    for (auto i = N - 1; i-- > 0; )
        x[i] = (x[i] - ud[i] * x[i + 1])/d[i];
}