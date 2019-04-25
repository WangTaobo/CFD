#include "TDMA.hpp"

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

void TDMA::LinSolve (vector<double> &ud, vector<double> &d, vector<double> &ld, vector<double> &phi, vector<double> &r)
{
	vector<double> d_prime = d;
	vector<double> r_prime = r;
	vector<double> phi_prime = phi;

	for (auto i = 1; i < N; i++) 
	{
		m = ld[i - 1] / d_prime[i - 1];
		d_prime[i] = d[i] - m*ud[i - 1];
		r_prime[i] = r[i] - m*r_prime[i - 1];
	}

	phi_prime = d_prime;
	phi_prime.back () = r_prime.back() / d_prime.back ();

	for (auto i = N - 2; i > -1; i--)
		phi_prime[i] = (r_prime[i] - ud[i]*phi_prime[i + 1]) / d_prime[i];
	
	phi = phi_prime;
}