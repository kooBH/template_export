import ctypes 
import numpy as np
from numpy.ctypeslib import ndpointer


class ALGO(object):
    
    def __init__(self, path,):
        self.n_hop = 256
        self.n_channels = 4
        self.n_sources  =1
        
        self.lib = ctypes.cdll.LoadLibrary(path)
        
        self.lib.ALGO_construct.argtypes = []
        self.lib.ALGO_construct.restype = ctypes.c_void_p

        self.lib.ALGO_process.argtypes = [ctypes.c_void_p, ndpointer(ctypes.c_int16,flags="C_CONTIGUOUS") , ndpointer(ctypes.c_int16,flags="C_CONTIGUOUS") ] 
        self.lib.ALGO_process.restype = ctypes.c_void_p

        self.lib.ALGO_release.argtypes = [ctypes.c_void_p]
        self.lib.ALGO_release.restype = ctypes.c_void_p

        self.obj = self.lib.ALGO_construct()
        
        self.buf_in =  np.zeros(self.n_hop*self.n_channels,dtype=np.int16)
        self.buf_out =  np.zeros(self.n_hop * self.n_sources,dtype=np.int16)
      

    def Process(self, sample_in):
        
        for i in range(self.n_hop*self.n_channels):
            self.buf_in[i] = int(sample_in[i]*32768.0)
        
        self.lib.ALGO_process(self.obj,self.buf_in,self.buf_out)
        
        sample_out = np.zeros(self.n_hop)
        
        for i in range(self.n_hop*self.n_sources) :
            sample_out[i] = self.buf_out[i]/32768.0
        
        return sample_out
    
    def Release(self):
        self.lib.ALGO_release(self.obj)