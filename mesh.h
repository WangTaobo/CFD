#pragma once

#ifndef MESH_H
#define MESH_H

class Mesh1D
{
public:
  Mesh1D();
  Mesh1D(double L, int N, double alpha);
  ~Mesh1D();
  virtual void BuildMesh (bool method, double* x_pt, double* x_fc, double* dx, double* Dx);
  virtual void MethodA (double* x_pt, double* x_fc, double* dx, double* Dx);
private:
  int N;
  double alpha = 1.0;
  double L;
};

#endif