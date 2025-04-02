import pyaudio
import soundfile as sf
import numpy as np
import os
from ALGO import ALGO

class WavStreamWriter:
    def __init__(self, filename, samplerate=16000, channels=1):
        self.file = sf.SoundFile(
            filename,
            mode='w',
            samplerate=samplerate,
            channels=channels,
            format='WAV',
            subtype='PCM_16'
        )

    def write(self, data: np.ndarray):
        self.file.write(data)

    def close(self):
        self.file.close()


class AlgorithmMicWrapper:
    def __init__(self, path_output):
        ## pyaudio
        self.p = pyaudio.PyAudio()
        self.format = pyaudio.paInt16
        self.in_channels = 4
        self.frames_per_buffer = 128
        self.out_channels = 1
        self.rate = 16000
        self.isInit = False
        self.stream = None

        ## Algorithm
        # Windows
        cur_path = os.path.dirname(os.path.abspath(__file__))
        if os.name == "nt" :
            self.path_lib = cur_path + "/ALGO.dll" 
        # Linux
        elif os.name == "posix" :
            self.path_lib = cur_path + "/ALGO.so"
        else : 
            print(f"ERROR::unknown os type : {os.name}")
            exit(-1)
        self.path_output = path_output  
    
    def audio_callback(self, in_data, frame_count, time_info, status):
        in_data = np.frombuffer(in_data, dtype=np.int16)
        out_data = self.algo.Process(in_data)
        self.output.write(out_data)
        return (None, pyaudio.paContinue)
    
    def OpenStream(self, device = 0 ):
        self.input_device_index = device
        self.stream = self.p.open(
            format=self.format,
            channels=self.in_channels,
            rate=self.rate,
            input=True,
            frames_per_buffer=self.frames_per_buffer,
            input_device_index=self.input_device_index,
            stream_callback=self.audio_callback
        )
        self.algo = ALGO(self.path_lib)
        self.output = WavStreamWriter(self.path_output, self.rate, self.out_channels)
        self.isInit = True
    
    def Start(self):
        if not self.isInit:
            print("Stream is not initialized")
            return
        self.stream.start_stream()

    def Stop(self):
        self.stream.stop_stream()
        self.stream.close()
        self.output.close()
        self.algo.Release()
        self.isInit = False

    def ListDevices(self):
        print("Input devices:\n")
        
        for i in range(self.p.get_device_count()):
            dev_info = self.p.get_device_info_by_index(i)
            if dev_info['maxInputChannels'] > 0:
                print(f"[{i}]{dev_info['name']}\n- channels: {dev_info['maxInputChannels']}\n - samplerate: {int(dev_info['defaultSampleRate'])}")

if __name__ == "__main__":
    audio = AlgorithmMicWrapper("../data/output.wav")
    audio.ListDevices()

    device = int(input("Select input device by index: "))
    audio.OpenStream(device)
    audio.Start()
    print("Recording started")

    try:
        while audio.stream.is_active():
            pass  
    except KeyboardInterrupt:
        print("Recording stopped")
        audio.Stop()










