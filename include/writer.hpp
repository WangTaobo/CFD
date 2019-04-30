#pragma once

#ifndef WRITER_H
#define WRITER_H

#include <vector>

using namespace std;

class Writer
{
public:
  Writer();
  virtual ~Writer();
  virtual void WriteOutput(int N, vector<double> &phi, vector<double>&x_pt, vector<double> &dx,
 vector<double> &Dx, double L, double T_b, double T_inf, double h, double P, double k, double A, double omega);
};

#endif