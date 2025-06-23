#include "ALGO_decl.h"


ALGO::ALGO() {

	data_in = new DTYPE[n_channels* n_hop];
	memset(data_in, 0, sizeof(DTYPE) * n_channels * n_hop);
	data_out = new DTYPE[n_sources* n_hop];
	memset(data_out, 0 ,sizeof(DTYPE)*n_sources*n_hop);

	printf("Algorithm initilized.\n");

}

ALGO::~ALGO() {
	delete[] data_in;
	delete[] data_out;
	printf("Algorithm released.\n");


}

void ALGO::process(DTYPE* buf_in, DTYPE* buf_out) {

	// by passing
	for (int ch = 0; ch < n_sources; ch++)
		for(int idx = 0; idx < n_hop;idx++)
			buf_out[idx*n_sources + ch] = buf_in[idx*n_channels + ch];
}

void ALGO::Process(short* buf_in, short* buf_out) {

	for (int i = 0; i < n_channels * n_hop; i++) {
		data_in[i] = static_cast<DTYPE>(buf_in[i])/32768.0;
	}
	process(data_in, data_out);
	for (int i = 0; i < n_sources * n_hop; i++) {
    buf_out[i] = static_cast<short>(data_out[i] * 32768.0);
  }

}


void ALGO::Process(float* buf_in, float* buf_out) {

	for (int i = 0; i < n_channels*n_hop; i++)
    data_in[i] = static_cast<DTYPE>(buf_in[i]);
  process(data_in, data_out);
  for (int i = 0; i < n_sources*n_hop; i++)
    buf_out[i] = static_cast<float>(data_out[i]);

}

