#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "mesh.h"
#include "FVM.h"
#include "TDMA.h"
#include "writer.h"
#include "gnuplot.h"

using namespace std;

int main(int argc, char* argv[])
{
  // GET INPUTS FROM RUN.SH
  int N = atoi(argv[1]); // number of control volumes
  double L = stod(argv[2]); // fin's length
  double alpha = stod(argv[3]); // mesh refinement factor
  double h = stod(argv[4]); // film coefficient
  double k = stod(argv[5]); // thermal conductivity
  double P = stod(argv[6]); // wet perimeter
  double A = stod(argv[7]); // area
  double T_inf = stod(argv[8]); // enviroment temperature
  double T_b = stod(argv[9]); // fin base temperature

  // ALLOCATE ARRAYS
  double* ud = new double[N - 1]{}; // upper diagonal array
  double* d = new double[N]{}; // diagonal array
  double* ld = new double[N - 1]{}; // lower diagonal array
  double* x = new double[N]{}; // solution array
  
  double* x_pt = new double[N] {}; // mesh points zeros array
  double* x_fc = new double[N - 1] {}; // mesh volume faces zeros array
  double* dx = new double[N - 1] {}; // point distance (δx) zeros array
  double* Dx = new double[N] {}; // face distance (Δx) zeros array

  // INITIALIZE CLASSES
  Mesh1D* mesh = new Mesh1D(L, N, alpha);
  FVM* fvm = new FVM(N, h, P, k, A, T_inf, T_b);
  TDMA* solver = new TDMA(N);
  Writer* writer = new Writer ();
  Gnuplot* plot = new Gnuplot();

  // COMPUTE SOLUTION
  mesh->BuildMesh(0, x_pt, x_fc, dx, Dx);
  fvm->Assemble(ud, d, ld, x, dx, Dx);
  solver->Solve(ud, d, ld, x);
  writer->WriteOutput(N, x, x_pt);
  plot->Operator("set style line 1 linecolor rgb \'#0060ad\' linetype 1 linewidth 2 pointtype 7 pointsize 1.5");
  plot->Operator("set yrange [295:355]");
  plot->Operator("set ylabel \'Temperatura [K]\'");
  plot->Operator("set xlabel \'x [m]\'");
  plot->Operator("set xrange [0:1.50]");
  plot->Operator("plot \'./solution.dat\' with linespoints linestyle 1 notitle");

  // FREE MEMORY
  delete mesh, fvm, solver, writer, plot;

  return 0;
}