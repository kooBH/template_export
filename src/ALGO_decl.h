#ifndef _H_ALGO_DECL_H_
#define _H_ALGO_DECL_H_

#include "ALGO.h"
#include "exp_chrono.h"
#include "STFT.h"

// double or float
#define DTYPE double

class ALGO {
private :
  DTYPE *data_in, *data_out;
  int n_channels = 4;
  int n_sources = 1;
  int n_hop = 128;

  // Actual process
  void process(DTYPE* buf_in, DTYPE* buf_out);

public :
  ALGO();
  ~ALGO();

  // External Interface
  void Process(short* buf_in, short* buf_out);
  void Process(float* buf_in, float* buf_out);
};


#endif
