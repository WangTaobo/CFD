#pragma once

#ifndef TDMA_H
#define TDMA_H

#include <vector>
using namespace std;

class TDMA
{
public:
  TDMA ();
  TDMA (int N);
  virtual ~TDMA ();
  virtual void LinSolve (vector<double> &ud, vector<double> &d, vector<double> &ld, vector<double> &phi, vector<double> &r);
private:
  // Initialize variables
  int N = 0;
  double m = 0.0;
};

#endif