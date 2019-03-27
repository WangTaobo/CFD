#pragma once

#ifndef TDMA_H
#define TDMA_H

class TDMA
{
public:
  TDMA ();
  TDMA (int N);
  ~TDMA ();
  virtual void Solve (double* ud, double* d, double* ld, double* x);
private:
  int N;
  double m;
};

#endif