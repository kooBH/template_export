#include "algo_decl.h"

void * ALGO_construct() {
	return new ALGO();
}

void ALGO_process(void* obj, short* buf_in, short* buf_out) {
reinterpret_cast<ALGO*>(obj)->Process(buf_in, buf_out);
}

void ALGO_release(void* obj) {
	delete reinterpret_cast<ALGO*>(obj);
}



