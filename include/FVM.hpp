#ifndef FVM_H
#define FVM_H

#include <vector>
using namespace std;

class FVM
{
public:
  FVM ();
  FVM (int N, double Sp, double Sc, double h, double T_inf, double T_b, double A);
  virtual ~FVM ();
  virtual void Assemble (vector<double> &ud, vector<double> &d, 
  vector<double> &ld, vector<double> &r, vector<double> &dx, vector<double> &Dx, vector<double> &gamma);
protected:
  int N;
  double Sc, Sp, h, T_inf, phib, A;
};

#endif