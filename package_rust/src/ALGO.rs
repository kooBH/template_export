use std::os::raw::{c_void, c_int, c_short, c_float, c_double};

#[link(name = "MYLIB")]
unsafe extern "C" {
    fn ALGO_construct() -> *mut c_void;
    fn ALGO_release(obj: *mut c_void);

    fn ALGO_process_int16(obj: *mut c_void, buf_in: *const i16, buf_out: *mut i16);
    fn ALGO_process_int32(obj: *mut c_void, buf_in: *const i32, buf_out: *mut i32);
    fn ALGO_process_fp32(obj: *mut c_void, buf_in: *const f32, buf_out: *mut f32);
    fn ALGO_process_fp64(obj: *mut c_void, buf_in: *const f64, buf_out: *mut f64);
}

pub struct AlgoEngine {
    instance: *mut c_void,
}

impl AlgoEngine {
    /// Initialize the C++ Algorithm object
    pub fn new() -> Self {
        let ptr = unsafe { ALGO_construct() };
        if ptr.is_null() {
            panic!("Critical: Failed to allocate C++ object via AlgoEngine_construct");
        }
        AlgoEngine { instance: ptr }
    }

    pub fn process_i16(&self, input: &[i16], output: &mut [i16]) {
        unsafe { ALGO_process_int16(self.instance, input.as_ptr(), output.as_mut_ptr()) };
    }

    pub fn process_i32(&self, input: &[i32], output: &mut [i32]) {
        unsafe { ALGO_process_int32(self.instance, input.as_ptr(), output.as_mut_ptr()) };
    }

    pub fn process_f32(&self, input: &[f32], output: &mut [f32]) {
        unsafe { ALGO_process_fp32(self.instance, input.as_ptr(), output.as_mut_ptr()) };
    }

    pub fn process_f64(&self, input: &[f64], output: &mut [f64]) {
        unsafe { ALGO_process_fp64(self.instance, input.as_ptr(), output.as_mut_ptr()) };
    }
}

impl Drop for AlgoEngine {
    fn drop(&mut self) {
        unsafe {
            ALGO_release(self.instance);
            // Optional: for debugging
            // println!("C++ object successfully released.");
        }
    }
}

