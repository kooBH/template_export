#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#include "WAV.h"
#include <string>
#include <filesystem>
#include "algorithm_wrapper.h"
#include "RtInput.h"
#include <time.h> //for check process time

// WAV_OR_MIC
// 1 : wav file input
// 0 : mic stream input
#define WAV_OR_MIC 1


void AudioProbe();
int GetDeviceID();

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

	ALGO* proc = ALGO_construct();

	
	#if WAV_OR_MIC
	// WAV IO
	WAV input;
	WAV ref;

	input.OpenFile("input.wav");
	ref.OpenFile("ref.wav");
#else
	
	// Find Device by Name
	const char* deviceName = "mpUSB";
	int device = 0;

	RtAudio::DeviceInfo info;
	RtAudio adc;
	
	AudioProbe();
	int device = GetDeviceID();
	
	short* temp_in = new short[(in_channels + ref_channels) * n_hop];
	int n_channels = in_channels + ref_channels;
	RtInput input(device,n_channels,sr,n_hop,n_fft,n_hop);

	// Save inputs for debugging
	WAV raw(n_channels, sr);
	raw.NewFile("raw.wav");

#endif

#if WAV_OR_MIC
	while (!input.IsEOF()) {
		input.ReadUnit(buf_in, n_hop * n_channel);
#else

	input.Start();
	while (input.IsRunning()) {

		if (input.data.stock.load() >= n_hop * n_channels)
			input.GetBuffer(temp_in);
		else
			continue;

		for (int i = 0; i < n_hop; i++) {
			for (int sensor = 0; sensor < in_channels; sensor++) {
				buf_in[in_channels * i + sensor] = temp_in[(n_channels)*i + sensor];
			}
			for (int channel = 0; channel < ref_channels; channel++) {
				ref_in[ref_channels * i + channel] = temp_in[(n_channels)*i + in_channels + channel];
			}
		}

#endif
		ALGO_process(proc, buf_in, buf_out);
		output.Append(buf_out, n_hop * 1);
#if !WAV_OR_MIC
	raw.Append(temp_in, n_channels * n_hop);
#endif
	}
	
#if WAV_OR_MIC
	input.Finish();

#else
	input.Stop();
	raw.Finish();

#endif
	output.Finish();


	delete[] buf_in;
	delete[] buf_out;

	ALGO_release(proc);
	
	return 0;
}

void AudioProbe(){
	
	RtAudio::DeviceInfo info;
	RtAudio adc;
    int	nDevice = adc.getDeviceCount();
	std::cout << "api : " << adc.getCurrentApi() << "\n";
	if (nDevice < 1) {
		std::cout << "\nNo audio devices found!\n";
		exit(-1);
		return 0;
	}
	else {
		std::cout << "Total Device : " << nDevice << "\n\n";
		for (int i = 0; i < nDevice; i++) {
			info = adc.getDeviceInfo(i);
				if (info.inputChannels >= 1) {
					std::cout << "device = " << i << "\n";
					std::cout << "name = " << info.name << "\n";
					std::cout << "maximum input channels = " << info.inputChannels << "\n";
					std::cout << "maximum output channels = " << info.outputChannels << "\n";
					std::cout << "Samplerates : ";
					for (auto sr : info.sampleRates)
						std::cout << sr << " ";
					std::cout << "\n";
					std::cout << "----------------------------------------------------------" << "\n";
			}
		}
	}
}

int GetDeviceID(){
	
	
}

