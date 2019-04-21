#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>
using namespace std;

class Mesh1D
{
public:
  Mesh1D();
  Mesh1D(double L, int N, double alpha);
  ~Mesh1D();
  virtual void BuildMesh (bool method, vector<double> &x_pt, 
                        vector<double> &x_fc, vector<double> &dx, vector<double> &Dx);
  virtual void MethodA (vector<double> &x_pt, vector<double> &x_fc, 
                        vector<double> &dx, vector<double> &Dx);
private:
  // Initialized with default values
  int N = 1;
  double alpha = 1.0;
  double L = 1.0;
};

#endif