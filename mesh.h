#pragma once

#ifndef MESH_H
#define MESH_H

class Mesh1D
{
public:
  Mesh1D ();
  Mesh1D (double L, int N);
  ~Mesh1D ();
  virtual void BuildMesh (bool method, double* x_pt, double* x_fc);
  virtual void MethodA (double* x_pt, double* x_fc);
  virtual void MethodB (double* x_pt, double* x_fc);
private:
  int N;
  double alpha = 1.0;
  double L;
};

#endif