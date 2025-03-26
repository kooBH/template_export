#ifndef _H_ALGO_DECL_H_
#define _H_ALGO_DECL_H_

#include "ALGO.h"
#include "exp_chrono.h"
#include "STFT.h"


class ALGO {

private :
  // Actual process
  void process(double* buf_in, double* buf_out);

public :
  ALGO();
  ~ALGO();

  // External Interface
  void Process(short* buf_in, short* buf_out);
};


#endif
