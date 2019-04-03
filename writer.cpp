#include <fstream>
#include <iostream>
#include "writer.h"

Writer::Writer()
{
}

Writer::~Writer()
{
}

void Writer::WriteOutput(int N, double* x, double* x_pt)
{
  std::ofstream outfile;
  outfile.open("solution.dat");
  outfile << "#x" << " " << "y" << std::endl;
  for (auto i = 0; i < N; i++) 
  {
    outfile << x_pt[i] << " " << x[i] << std::endl;
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