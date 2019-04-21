#pragma once

#ifndef FVM_H
#define FVM_H

#include <vector>
using namespace std;

class FVM
{
public:
  FVM ();
  FVM (int N, double Sp, double Sc, double gamma, double h, double T_inf, double T_b);
  ~FVM ();
  virtual void Assemble (vector<double> &ud, vector<double> &d, 
  vector<double> &ld, vector<double> &r, vector<double> &dx, vector<double> &Dx);
private:
  int N;
  double Sc, Sp, gamma, h, T_inf, phib;
};

#endif