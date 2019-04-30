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
 vector<double> &Dx, double L, double T_b, double T_inf, double h, double P, double k, double A, double omega)
{
  std::ofstream outfile;
  outfile.open("./Output/solution.dat");
  outfile << "#x" << " " << "y" << std::endl;
  for (auto i = 0; i < N; i++) 
  {
    outfile << x_pt[i] / L << " " << (phi[i] - T_inf) / (T_b - T_inf) << std::endl;
  }
  outfile.close();

  outfile.open("./Output/balance.dat");
  outfile << "#Conservation of energy" << std::endl;
  double kb = (k*(1 + omega*(phi[0] - T_inf)/(T_b - T_inf)*(phi[0] - T_inf)/(T_b - T_inf)*(phi[0] - T_inf)/(T_b - T_inf)));
  double k1 = (k*(1 + omega*(phi[1] - T_inf)/(T_b - T_inf)*(phi[1] - T_inf)/(T_b - T_inf)*(phi[1] - T_inf)/(T_b - T_inf)));
  double ke = 2*kb*k1 / (k1 + kb);
  outfile << "#Heat conducted throught the base of the fin " << - A*ke* (phi[1] - phi[0])/dx[0] << std::endl;
  double acc_source = 0.0;
  for (auto i = 1; i < N; i++) 
  {
    acc_source += (-h*P*phi[i] + h*P*T_inf)*Dx[i];
  }
  acc_source += -h*A*(phi.back() - T_inf);
  outfile << "#Heat convected throught the fin " << acc_source << std::endl;
  outfile.close();
}