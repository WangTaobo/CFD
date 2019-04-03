#include "mesh.h"
#include <cmath>
#include <iostream>

Mesh1D::Mesh1D ()
{
}

Mesh1D::Mesh1D(double L, int N, double alpha)
{
  this->L = L;
  this->N = N;
  this->alpha = alpha;
}

Mesh1D::~Mesh1D()
{
}

void Mesh1D::BuildMesh(bool method, double* x_pt, double* x_fc, double* dx, double* Dx)
{   
  if (method == 0)
      MethodA (x_pt, x_fc, dx, Dx);
  else // TODO: call method B
    return;
}

void Mesh1D::MethodA(double* x_pt, double* x_fc, double* dx, double* Dx)
{    
  for (auto i = 1; i < N; i++)
  {
      x_pt[i] = L*pow((i) / (static_cast<double>(N) - 1), alpha);
      x_fc[i - 1] = (x_pt[i] + x_pt[i - 1]) / 2;
      dx[i - 1] = x_pt[i] - x_pt[i - 1];
  }

  for(auto i = 1; i < N; i++)
  {
    Dx[i] = x_fc[i] - x_fc[i - 1];
  }

  Dx[0] = x_fc[0] - x_pt[0];
  Dx[N - 1] = x_pt[N - 1] - x_fc[N - 2];
}