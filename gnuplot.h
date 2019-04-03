#pragma once

#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <iostream>
#include <string>

using namespace std;

class Gnuplot 
{
public:
    Gnuplot();
    ~Gnuplot();
    FILE* gnuplotpipe;
    void Operator (const string & command);
};

#endif