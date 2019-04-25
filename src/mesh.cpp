#include "mesh.hpp"
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

void Mesh1D::BuildMesh(bool method, vector<double> &x_pt, vector<double> &x_fc,
                      vector<double> &dx, vector<double> &Dx)
{   
  !method? MethodA (x_pt, x_fc, dx, Dx) : MethodA (x_pt, x_fc, dx, Dx); // TODO: PUT METHOD B
}

void Mesh1D::MethodA(vector<double> &x_pt, vector<double> &x_fc, vector<double> &dx, vector<double> &Dx)
{
  for (unsigned int i = 1; i < x_pt.size(); i++)
  {
      x_pt[i] = L*pow((i) / (static_cast<double>(N) - 1.0), alpha);
      x_fc[i] = (x_pt[i] + x_pt[i - 1]) / 2;
      dx[i - 1] = x_pt[i] - x_pt[i - 1];
  }

  x_fc.back() = L;

  for(unsigned int i = 0; i < Dx.size(); i++)
  {
    Dx[i] = x_fc[i + 1] - x_fc[i];
  }
}