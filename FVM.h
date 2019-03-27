#pragma once

#ifndef FVM_H
#define FVM_H

class FVM
{
public:
  FVM (double k1, double k2, double k3, double k4, double k5, 
      double k6, double L, double L1, double L2, double L3, 
      double L4, double L5, double L6);
  ~FVM ();
  virtual void Assemble (double* ud, double* d, double* ld, double* x);
private:
   double k1, k2, k3, k4, k5, k6, L, L1, L2, L3, L4, L5, L6;
};

#endif