#ifndef _H_ALGO_H_
#define _H_ALGO_H_

#ifdef _WIN32
#ifdef _EXPORT_
#define DLL_PREFIX __declspec(dllexport)
#else
#define DLL_PREFIX  __declspec(dllimport)
#endif
#else
#define DLL_PREFIX 
#endif

extern "C" DLL_PREFIX void* ALGO_construct();
extern "C" DLL_PREFIX void ALGO_release(void* obj);
extern "C" DLL_PREFIX void ALGO_process_int16(void* obj, short* buf_in, short* buf_out);
extern "C" DLL_PREFIX void ALGO_process_fp32(void* obj, float* buf_in, float* buf_out);

#endif