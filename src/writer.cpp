#include <fstream>
#include <iostream>
#include "writer.hpp"

Writer::Writer()
{
}

Writer::~Writer()
{
}

void Writer::WriteOutput(int N, vector<double> &phi, vector<double>&x_pt, vector<double> &dx,
 vector<double> &Dx, double L, double T_b, double T_inf)
{
  std::ofstream outfile;
  outfile.open("./Output/solution.dat");
  outfile << "#x" << " " << "y" << std::endl;
  for (auto i = 0; i < N; i++) 
  {
    outfile << x_pt[i] / L << " " << (phi[i] - T_inf) / (T_b - T_inf) << std::endl;
  }
  outfile.close();

  /*outfile.open("balance.dat");
  outfile << "Heat balance over nodes" << std::endl;
  
  for (auto i = 1; i < N - 1; i++) 
  {
    outfile << - 1.5 * (x[i] - x[i - 1]) / x_pt[i - 1] << std::endl;
  }
  outfile.close();*/
}