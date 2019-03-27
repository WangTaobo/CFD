#include <iostream>
#include "writer.h"

Writer::Writer()
{
}

Writer::~Writer()
{
}

void Writer::WriteOutput(int N, double* x)
{
  std::cout << "x = (";
  for (auto i = 0; i < N; i++)
  {
      std::cout << x[i];
      if (i < N-1)
          std:: cout << ", ";
  }
  std::cout << ")" << std::endl;
}