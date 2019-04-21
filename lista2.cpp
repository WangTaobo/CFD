#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "mesh.h"
#include "FVM.h"
#include "TDMA.h"
#include "writer.h"
#include "gnuplot.h"

using namespace std;

int main(int argc, char* argv[])
{
/*
**************** PRE-PROCESSING ***********
*/
  // GET INPUTS FROM RUN.SH
  int N = atoi(argv[1]); // number of control volumes
  double L = stod(argv[2]); // fin's length
  double alpha = stod(argv[3]); // mesh refinement factor
  double h = stod(argv[4]); // film coefficient
  double k = stod(argv[5]); // thermal conductivity
  double P = stod(argv[6]); // wet perimeter
  double A = stod(argv[7]); // area
  double T_inf = stod(argv[8]); // room temperature
  double T_b = stod(argv[9]); // fin base temperature
  
  constexpr auto LINEAR = 1.0;


  // INPUTS TO STANDARD FORMAT
  double Sp = - h*P / (A);
  double Sc = h*P*T_inf / (A);
  double gamma = k;

  // INITIALIZE VECTORS WITH ZEROS
  vector<double> ud (N - 1, 0.0); // upper diagonal
  vector<double> d (N, 0.0); // diagonal
  vector<double> ld (N - 1, 0.0); // lower diagonal
  vector<double> phi (N, 0.0); // solution
  vector<double> r (N, 0.0); // system response [ud d ld]*phi = r
  
  vector<double> x_pt (N, 0.0); // domain nodes
  vector<double> x_fc (N + 1, 0.0); // domain faces
  vector<double> dx (N - 1, 0.0); // distance between nodes
  vector<double> Dx (N, 0.0); // distance between faces
  
  // INITIALIZE CLASSES
  Mesh1D* mesh = new Mesh1D(L, N, alpha);
  FVM* fvm = new FVM(N, Sp, Sc, gamma, h, T_inf, T_b);
  TDMA* solver = new TDMA(N);
  Writer* writer = new Writer ();
  Gnuplot plot;
/*
**************** PROCESSING ***************
*/
  // COMPUTE SOLUTION
  mesh->BuildMesh(false, x_pt, x_fc, dx, Dx);

  if (LINEAR) 
  {
	  fvm->Assemble (ud, d, ld, r, dx, Dx);
	  solver->Solve (ud, d, ld, phi, r);
	  writer->WriteOutput (N, phi, x_pt, dx, Dx, L, T_b, T_inf);
  }
/*
**************** POST-PROCESSING ***********
*/
  plot("set ylabel \'Temperatura [-]\'");
  plot("set xlabel \'x/L [-]\'");
  plot("plot \'./Output/solution.dat\' with linespoints title \'Numerico\'");
  
  // FREE MEMORY
  delete mesh, fvm, solver, writer;

  return 0;
}