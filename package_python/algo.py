import ctypes 
import numpy as np
from numpy.ctypeslib import ndpointer


class ALGO(object):
    
    def __init__(self, path,n_channels = 4, n_hop=128,n_sources = 1, dtype = np.int16):
        self.n_hop = n_hop
        self.n_channels = n_channels
        self.n_sources  = n_sources
        self.dtype = dtype
        
        self.lib = ctypes.cdll.LoadLibrary(path)
        
        self.lib.ALGO_construct.argtypes = []
        self.lib.ALGO_construct.restype = ctypes.c_void_p

        self.lib.ALGO_process_int16.argtypes = [ctypes.c_void_p, ndpointer(ctypes.c_int16,flags="C_CONTIGUOUS") , ndpointer(ctypes.c_int16,flags="C_CONTIGUOUS") ] 
        self.lib.ALGO_process_int16.restype = ctypes.c_void_p

        self.lib.ALGO_process_fp32.argtypes = [ctypes.c_void_p, ndpointer(ctypes.c_float,flags="C_CONTIGUOUS") , ndpointer(ctypes.c_float,flags="C_CONTIGUOUS") ] 
        self.lib.ALGO_process_fp32.restype = ctypes.c_void_p

        self.lib.ALGO_release.argtypes = [ctypes.c_void_p]
        self.lib.ALGO_release.restype = ctypes.c_void_p

        self.obj = self.lib.ALGO_construct()
        
        self.buf_in =  np.zeros(self.n_hop*self.n_channels,dtype=self.dtype)
        self.buf_out =  np.zeros(self.n_hop * self.n_sources,dtype=self.dtype)

    def Process(self, sample_in):
        if self.dtype == np.float32:
            return self.ProcessFP32(sample_in)
        elif self.dtype == np.int16:
            return self.ProcessInt16(sample_in)
        else:
            raise ValueError(f"Unsupported data type  : {self.dtype}")

    def ProcessFP32(self, sample_in):
        print(f"{type(sample_in)} {sample_in.dtype}")
        self.lib.ALGO_process_fp32(self.obj,sample_in,self.buf_out)
        #print(f"ProcessFP32 : {np.sum(np.abs(sample_in))} {np.sum(np.abs(self.buf_out))}")
        return self.buf_out
    
    def ProcessInt16(self, sample_in):  
        self.lib.ALGO_process_int16(self.obj,sample_in,self.buf_out)
        #print(f"ProcessInt16 : {np.sum(np.abs(sample_in))} {np.sum(np.abs(self.buf_out))}")
        return self.buf_out
    
    def Release(self):
        self.lib.ALGO_release(self.obj)