#include <cstdlib>
#include<string>
#include "mesh.h"
#include "FVM.h"
#include "TDMA.h"
#include "writer.h"

int main(int argc, char* argv[])
{
  // GET INPUTS FROM COMMAND LINE
  
  int N = std::atoi(argv[1]); // Number of control volumes
  double k1 = 8000;
  double k2 = 9000;
  double k3 = 15000;
  double k4 = 12000;
  double k5 = 10000;
  double k6 = 18000;

  double L = std::stod(argv[2]); // Length of Fin
  double L1 = 0.18;
  double L2 = 0.22;
  double L3 = 0.26;
  double L4 = 0.19;
  double L5 = 0.15;
  double L6 = 0.30;

  // ALLOCATE ARRAYS
  
  double* ud = new double[N-1]{}; // upper diagonal array
  double* d = new double[N]{}; // diagonal array
  double* ld = new double[N-1]{}; // lower diagonal array
  double* x = new double[N]{}; // solution array
  
  double* x_pt = new double[N] {}; // mesh points array
  double* x_fc = new double[N] {}; // mesh volume faces array
  
  // INITIALIZE CLASSES
  
  Mesh1D* mesh = new Mesh1D(L, N);
  FVM* fvm = new FVM(k1, k2, k3, k4, k5, k6, L, L1, L2, L3, L4, L5, L6);
  TDMA* solver = new TDMA(N);
  Writer* writer = new Writer ();

  // COMPUTE SOLUTION

  mesh->BuildMesh(0, x_pt, x_fc);
  fvm->Assemble(ud, d, ld, x);
  solver->Solve(ud, d, ld, x);
  writer->WriteOutput(N, x);

  // FREE MEMORY
  delete mesh, fvm, solver, writer;

  return 0;
}