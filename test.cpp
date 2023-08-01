#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#include "WAV.h"
#include <string>
#include <filesystem>
#include "algorithm_wrapper.h"
#include <time.h> //for check process time


int main() {

	#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 1286;
#endif

	int n_channel = 7;
	int sr = 16000;
	int n_fft = 1024;
	int n_hop = 256;	


	int length;
	WAV input(n_channel, sr);
	WAV output(1, sr);

	short* buf_in = new short[n_channel * n_hop];
	short* buf_out = new short[1* n_hop];

	ALGO* proc = ALGO_construct(n_channel, "../config.json");

	std::string InputFileName = "1-1-1";
	input.OpenFile(InputFileName + ".wav");
	output.NewFile(InputFileName + "_output.wav");	

	while (!input.IsEOF()) {
		length = input.ReadUnit(buf_in, n_hop * n_channel);
		ALGO_process(proc, buf_in, buf_out);
		output.Append(buf_out, n_hop * 1);
	}
	
	output.Finish();
	input.Finish();

	delete[] buf_in;
	delete[] buf_out;


	ALGO_release(proc);
	
	return 0;
}

