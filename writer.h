#pragma once

#ifndef WRITER_H
#define WRITER_H

class Writer
{
public:
  Writer();
  ~Writer();
  virtual void WriteOutput(int N, double *x, double* x_pt);
};

#endif