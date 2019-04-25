#include "gnuplot.hpp"

Gnuplot::Gnuplot()
{
    #ifdef __linux__
        gnuplotpipe = popen("gnuplot -persist", "w");
    #elif _WIN32
        gnuplotpipe = _popen("gnuplot -persist", "w");
    #endif
    if(!gnuplotpipe)
        cerr << ("Gnuplot not found");
}

Gnuplot::~Gnuplot()
{
    #ifdef __linux__
        fprintf(gnuplotpipe, "exit \n");
        pclose(gnuplotpipe);
    #elif _WIN32
        _fprintf(gnuplotpipe, "exit \n");
        _pclose(gnuplotpipe);
    #endif
}

void Gnuplot::operator ()(const string & command)
{
    #ifdef __linux__
        fprintf(gnuplotpipe, "%s\n", command.c_str());
        fflush(gnuplotpipe);
    #elif _WIN32
        _fprintf(gnuplotpipe, "%s\n", command.c_str());
        _fflush(gnuplotpipe);
    #endif
}