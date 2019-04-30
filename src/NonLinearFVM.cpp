#include "NonLinearFVM.hpp"
#include <cmath>

NonLinearFVM::NonLinearFVM()
{
}

NonLinearFVM::NonLinearFVM(int N, double Sp, double Sc, double h, double T_inf, double T_b, double A) 
                          : FVM(N, Sp, Sc, h, T_inf, T_b, A)
{
}

NonLinearFVM::~NonLinearFVM()
{
}

double NonLinearFVM::dAldTp(double k, double omega, double kl, double kp, double dx, double Tp)
{
    double dGpdTp = (3*k*omega*pow((Tp - T_inf), 2.0)) / pow((phib - T_inf), 3.0);
    
    double dAldT = (2/dx) * ((kl*kl - kp*kl) / pow((kl + kp), 3.0)) * dGpdTp;

    return A*dAldT;
}



void NonLinearFVM::Assemble(vector<double> &ud, vector<double> &d, 
                          vector<double> &ld, vector<double> &phi, 
                          vector<double> &r, vector<double> &dx,
                          vector<double> &Dx, vector<double> &gamma, double omega, double k)
{
    double gamma_l;
    
    fill(ld.begin(), ld.end(), 0.0);
    fill(ud.begin(), ud.end(), 0.0);
    fill(d.begin(), d.end(), 0.0);
    fill(r.begin(), r.end(), 0.0);

    vector<double> aw (N, 0.0);
    vector<double> ae (N, 0.0);

    // Compute al
    for (unsigned int i = 0; i < dx.size(); i++)
    {
        gamma_l = 2*gamma[i]*gamma[i + 1] / (gamma[i] + gamma[i + 1]);
        ae[i] = A*gamma_l / dx[i];
    }
    
    for (unsigned int i = 1; i < dx.size() + 1; i++)
    {
        gamma_l = 2*gamma[i]*gamma[i - 1] / (gamma[i] + gamma[i - 1]);
        aw[i] = A*gamma_l / dx[i - 1];
    }

    // Compute Tangent
    for (unsigned int i = 0; i < ld.size(); i++)
    {
        ld[i] = -aw[i + 1]; 
        if (i > 0) 
        {
            double dAwdTw = dAldTp(k, omega, gamma[i], gamma[i-1], dx[i], phi[i-1]);
            ld[i] += dAwdTw*(phi[i] - phi[i-1]);
        }
    }

    for (unsigned int i = 0; i < ud.size(); i++)
    {
        ud[i] = -ae[i]; 
        if (i < phi.size() - 1)
        {
            double dAedTe = dAldTp(k, omega, gamma[i], gamma[i+1], dx[i], phi[i+1]);
            ud[i] += dAedTe*(phi[i] - phi[i+1]);
        }
    }

    for (unsigned int i = 0; i < d.size(); i++)
    {
        d[i] = ae[i] + aw[i] - A * Sp * Dx[i];
        
        if (i > 0)
        {
            double dAwdTp = dAldTp(k, omega ,gamma[i-1], gamma[i], d[i], phi[i]);
            d[i] += dAwdTp*(phi[i] - phi[i-1]);
        }
        
        if (i < phi.size() - 1) 
        {
            double dAedTp = dAldTp(k, omega ,gamma[i+1], gamma[i], d[i], phi[i]);
            d[i] += dAedTp*(phi[i] - phi[i+1]);
        }
    }
    
    // Compute Residual
    for (unsigned int i = 0; i < r.size(); i++)
    {
        r[i] -= (aw[i] + ae[i] - A * Sp * Dx[i])*phi[i] -  A * Sc * Dx[i];
        if (i > 0)
        {
            r[i] -= - aw[i] * phi[i - 1];
        }
        
        if (i < phi.size() - 1)
        {
            r[i] -= - ae[i] * phi[i + 1];
        }
    }
    
    // Apply boundary conditions
    d[0] = 1.0; // left boundary
    ud[0] = 0.0; // left boundary
    r[0] = 0.0; // left boundary

    d.back() += A * h; // right boundary
    r.back() -=  A * h *(phi.back() - T_inf); // right boundary
}