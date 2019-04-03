#include "gnuplot.h"

Gnuplot::Gnuplot()
{
    gnuplotpipe = popen("gnuplot -persist", "w");
    if(!gnuplotpipe)
        cerr << ("Gnuplot not found");
}

Gnuplot::~Gnuplot()
{
    fprintf(gnuplotpipe, "exit \n");
    pclose(gnuplotpipe);
}

void Gnuplot::Operator (const string & command)
{
    fprintf(gnuplotpipe, "%s\n", command.c_str());
    fflush(gnuplotpipe);
}