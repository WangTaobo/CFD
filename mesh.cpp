#include "mesh.h"
#include <cmath>
#include <iostream>
Mesh1D::Mesh1D ()
{
}

Mesh1D::Mesh1D (double L, int N)
{
  this->L = L;
  this->N = N;
}

Mesh1D::~Mesh1D ()
{
}

void Mesh1D::BuildMesh (bool method, double* x_pt, double* x_fc)
{   
  if (method == 0) // "a" = 0 and "b" = 1
      MethodA (x_pt, x_fc);
  else
      MethodB (x_pt, x_fc);
    
}

void Mesh1D::MethodA (double* x_pt, double* x_fc)
{
  x_pt[0] = 0.0; // set initial point location
    
  for (auto i = 1; i < N; i++)
  {
      x_pt[i] = L*pow((i) / (static_cast<double>(N) - 1), alpha);
      x_fc[i] = (x_pt[i] + x_pt[i - 1]) / 2;
  }
}

void Mesh1D::MethodB (double* x_pt, double* x_fc)
{
  x_fc[0] = 0.0;
  
  for (auto i = 1; i < N; i++)
  {
      x_fc[i] = L*pow( i / (static_cast<double>(N) - 1) , alpha);
      x_pt[i] = (x_fc[i + 1] + x_fc[i]) / 2;
  }
}