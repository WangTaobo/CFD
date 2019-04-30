#include "mathlib.hpp"

mathlib::mathlib() 
{
}

mathlib::~mathlib() 
{
}

double mathlib::dot(const unsigned int n, vector<double> &x, vector<double> &y)
{
    double sum = 0.0;
    for(unsigned int i = 0; i < n; i++)
        sum += x[i]*y[i];
    return sum;
}

double mathlib::Norm(const unsigned int n, vector<double> &x)
{
    double sum = 0.0;
    for(unsigned int i = 0; i < n; i++)
        sum += x[i]*x[i];
    return sqrt(sum);
}