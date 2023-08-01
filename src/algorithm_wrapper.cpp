#include "algorithm_wrapper.h"


ALGO::ALGO() {


}

ALGO::~ALGO() {
	


}

void ALGO::process(short* buf_in, short* buf_out) {
}

ALGO* ALGO_construct() {
	return new ALGO();
}
void ALGO_process(ALGO* obj, short* buf_in, short* buf_out) {
obj->process(buf_in, buf_out);	
}
void ALGO_release(ALGO* obj) {
	delete obj;
}

