#pragma once

#ifndef FVM_H
#define FVM_H

class FVM
{
public:
  FVM ();
  FVM (int N, double h, double P, double k, double A, double T_inf, double T_b);
  ~FVM ();
  virtual void Assemble (double* ud, double* d, double* ld, double* x, double* dx, double* Dx);
private:
  int N;
  double Sc, Sp, gamma;
  double h, T_inf, T_b;
};

#endif