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

void TDMA::Solve (vector<double> &ud, vector<double> &d, vector<double> &ld, vector<double> &phi, vector<double> &r)
{
	vector<double> d_prime = d;
	phi = r; // copy r to phi
 
	for (auto i = 1; i < N; i++) 
	{
		m = ld[i - 1] / d_prime[i - 1];
		d_prime[i] -= m*ud[i - 1];
		phi[i] -= m*phi[i - 1];
	}

	phi.back () = phi.back () / d_prime.back ();

	for (auto i = N - 1; i-- > 0 ;)
		phi[i] = (phi[i] - ud[i]*phi[i + 1]) / d_prime[i];
}