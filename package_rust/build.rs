use std::env;
use std::fs;
use std::path::PathBuf;

fn main() {
    let out_dir = env::var("OUT_DIR").unwrap(); // Build artifact directory
    let manifest_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    
    // Path to your source DLL
    let dll_src = PathBuf::from(manifest_dir).join("lib").join("MYLIB.dll");
    
    // Tell cargo where to find the compiled library
    println!("cargo:rustc-link-search=native=./lib");
    println!("cargo:rustc-link-lib=MYLIB");

    println!("cargo:rerun-if-changed=lib/MYLIB.dll");
}