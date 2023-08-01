#ifdef _WIN32

#ifdef _EXPORT_
#define DLL_PREFIX __declspec(dllexport)
#else
#define DLL_PREFIX  __declspec(dllimport)
#endif

#else
#define DLL_PREFIX 

#endif

#include <fstream>
#include <string>
#include <iostream>



class ALGO {
private :
 

public :
  ALGO();
  ~ALGO();
  void process(short* buf_in, short* buf_out);
};


extern "C" DLL_PREFIX ALGO * ALGO_construct();
extern "C" DLL_PREFIX void ALGO_process(ALGO * obj, short* buf_in, short* buf_out);
extern "C" DLL_PREFIX void ALGO_release(ALGO * obj);
