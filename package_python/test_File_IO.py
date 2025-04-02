import librosa as rs
import soundfile as sf
import numpy as np
import os
from ALGO import ALGO

cur_path = os.path.dirname(os.path.abspath(__file__))
input = rs.load(cur_path+ "/../data/UMA8_4ch_16kHz_mictest.wav", mono=False, sr = 16000)[0]

n_hop = 128 
n_channels = input.shape[0]

# Windows
if os.name == "nt" :
    path_lib = cur_path + "/ALGO.dll" 
# Linux
elif os.name == "posix" :
    path_lib = cur_path + "/ALGO.so"
else : 
     print(f"ERROR::unknown os type : {os.name}")
     exit(-1)
processor = ALGO(path_lib,dtype=np.float32)

n_frame = int(input.shape[1]/n_hop)

interleaved_in = np.zeros(n_channels*input.shape[1],dtype=np.float32)

for i in range(n_channels):
    for j in range(input.shape[1]) : 
        interleaved_in[j*n_channels + i] = input[i,j]
        
data_out = []

for i in range(n_frame) :
    sample_in = interleaved_in[i*n_hop*n_channels : (i+1)*n_hop*n_channels]
    sample_out = processor.Process(sample_in)
    data_out.append([*sample_out])

#data_out = input[0, :]   # export 0ch for test. remove if before apply this template
data_out = np.array(data_out).flatten()

ALGO.Release(processor)

sf.write(cur_path + "/../data/output.wav",data_out,16000)