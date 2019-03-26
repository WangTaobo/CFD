#include "mesh.h"
#include <cmath>

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

void Mesh1D::BuildMesh (const char method)
{   
    if (method == 97) // "a" = 97 and "b" = 98
        MethodA ();
    else
        MethodB ();
    
}

void Mesh1D::MethodA ()
{
    for (auto i = 0; i < N; i++)
    {
        x_pt[i] = L*pow((i - 1) / (static_cast<double>(N) - 1), alpha);
        x_fc[i] = (x_pt[i] + x_pt[i - 1]) / 2
    }
}

void Mesh1D::MethodB ()
{
    for (auto i = 0; i < N; i++)
    {
        x_fc[i] = L*pow((i - 2) / (static_cast<double>(N) - 1) , alpha);
        x_pt[i] = (x_fc[i + 1] + x_fc[i]) / 2;
    }
}