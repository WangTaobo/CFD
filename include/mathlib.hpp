#ifndef MATHLIB_H
#define MATHLIB_H

#include <cmath>
#include <vector>

using namespace std;

class mathlib 
{
public:
    mathlib();
    virtual ~mathlib();
    virtual double dot(const unsigned int n, vector<double> &x, vector<double> &y);
    virtual double Norm(const unsigned int n, vector<double> &x);
};

#endif