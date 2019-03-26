#include "FVM.h"
#include "TDMA.h"
#include "writer.h"

int main()
{
  // INPUTS
  int N = 5;

  double k1 = 8000;
  double k2 = 9000;
  double k3 = 15000;
  double k4 = 12000;
  double k5 = 10000;
  double k6 = 18000;

  double L = 1.50;
  double L1 = 0.18;
  double L2 = 0.22;
  double L3 = 0.26;
  double L4 = 0.19;
  double L5 = 0.15;
  double L6 = 0.30;
  
  // ALLOCATE ARRAYS
  double* ud = new double[N-1]{};
  double* d = new double[N]{};
  double* ld = new double[N-1]{};
  double* x = new double[N]{};


  // INITIALIZE CLASS
  FVM* fvm = new FVM(k1, k2, k3, k4, k5, k6, L, L1, L2, L3, L4, L5, L6);
  TDMA* solver = new TDMA(N);
  Writer* writer = new Writer ();

  // RUN ROUTINE
  fvm->Assemble(ud, d, ld, x);
  solver->Solve(ud, d, ld, x);
  writer->WriteOutput(N, x);

  // FREE MEMORY
  delete fvm, solver, writer;

  return 0;
}