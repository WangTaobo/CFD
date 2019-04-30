#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "mesh.hpp"
#include "Picard.hpp"
#include "NewtonRaphson.hpp"
#include "writer.hpp"
#include "gnuplot.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc < 2)
    throw "No inputs !";


/*
**************** PRE-PROCESSING ***********
*/
  // GET INPUTS FROM COMMAND LINE
  int N = atoi(argv[1]); // number of control volumes
  double L = stod(argv[2]); // fin's length
  double alpha = stod(argv[3]); // mesh refinement factor
  double h = stod(argv[4]); // film coefficient
  double k = stod(argv[5]); // ref thermal conductivity
  double P = stod(argv[6]); // wet perimeter
  double A = stod(argv[7]); // area
  double T_inf = stod(argv[8]); // room temperature
  double T_b = stod(argv[9]); // fin base temperature
  double omega = stod(argv[10]);

  // INITIALIZE VECTORS
  vector<double> ud (N - 1, 0.0); // upper diagonal
  vector<double> d (N, 0.0); // diagonal
  vector<double> ld (N - 1, 0.0); // lower diagonal
  vector<double> r (N, 0.0); // system response [ud d ld]*phi = r

  vector<double> x_pt (N, 0.0); // domain nodes
  vector<double> x_fc (N + 1, 0.0); // domain faces
  vector<double> dx (N - 1, 0.0); // distance between nodes
  vector<double> Dx (N, 0.0); // distance between faces
  
  vector<double> phi (N, 0.0); // solution
  
  // BUILD MESH
  Mesh1D* mesh = new Mesh1D(L, N, alpha);
  mesh->BuildMesh(false, x_pt, x_fc, dx, Dx);
  
  // Set phi
  for (unsigned int i = 0; i < phi.size(); i++)
  {
    phi[i] = -((T_b - T_inf) / L)*x_pt[i] + T_b;
  }

  // INPUTS TO STANDARD FORMAT
  double Sp = - h*P / (A);
  double Sc = h*P*T_inf / (A);
  vector<double> gamma (N, k); // gamma initial values

  Picard* solver = new Picard(dx, Dx, ud, d, ld, r, omega,
                             k, N, Sp, Sc, phi, gamma, h, T_inf, T_b, A);
  Writer* writer = new Writer ();
  Gnuplot plot;
/*
**************** PROCESSING ***************
*/
  // COMPUTE SOLUTION
  
  phi = solver->Solve();
  writer->WriteOutput (N, phi, x_pt, dx, Dx, L, T_b, T_inf, h, P, k, A, omega);

/*
**************** POST-PROCESSING ***********
*/
  plot("set ylabel \'Temperatura [-]\'");
  plot("set xlabel \'x/L [-]\'");
  plot("plot \'./Output/solution.dat\' with lines title \'Picard\', \'./Output/solutionNewton.dat\' with points title \'Newton\'");
  
  // FREE MEMORY
  delete mesh;
  delete solver;
  delete writer;

  return 0;
}