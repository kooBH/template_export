#include "ALGO_decl.h"

void * ALGO_construct() {
	return new ALGO();
}

void ALGO_process_int16(void* obj, short* buf_in, short* buf_out) {
	reinterpret_cast<ALGO*>(obj)->Process(buf_in, buf_out);
}

void ALGO_process_int32(void* obj, int* buf_in, int* buf_out) {
	reinterpret_cast<ALGO*>(obj)->Process(buf_in, buf_out);
}

void ALGO_process_fp32(void* obj, float* buf_in, float* buf_out) {
	reinterpret_cast<ALGO*>(obj)->Process(buf_in, buf_out);
}

void ALGO_process_fp64(void* obj, double* buf_in, double* buf_out) {
	reinterpret_cast<ALGO*>(obj)->Process(buf_in, buf_out);
}


void ALGO_release(void* obj) {
	delete reinterpret_cast<ALGO*>(obj);
}



