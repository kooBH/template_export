#include <jni.h>
#include <vector>
#include <mutex>
#include <stdio.h>
#include "ALGO.h"
#include "WAV.h"

#define JVOID extern "C" JNIEXPORT void JNICALL
#define JBOOL extern "C" JNIEXPORT jboolean JNICALL
#define JINT extern "C" JNIEXPORT jint JNICALL
#define JSTRING extern "C" JNIEXPORT jstring JNICALL
#define JARRAY  extern "C" JNIEXPORT jobjectArray JNICALL

#include <android/log.h>
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "Native-lib", __VA_ARGS__);

// "_" -> "_1" for package name
JVOID  Java_com_mpwav_aos_1lib_MainActivity_run(JNIEnv *env, jobject thiz, jstring path_input,
                                                            jstring path_output) {
   float*buf_in,*buf_out;
   short* short_in, *short_out;

   int n_channels = 2;
   int n_hop = 384;
   int sr = 48000;

   const char* cstr_input = env->GetStringUTFChars(path_input, nullptr);
   const char* cstr_output = env->GetStringUTFChars(path_output, nullptr);

   short_in = new short[n_channels * n_hop];
   short_out = new short[n_channels * n_hop];
   buf_in = new float[n_channels * n_hop];
   buf_out = new float[n_channels * n_hop];

   WAV input(n_channels,sr);
   WAV output(n_channels,sr);

   LOGI("Open input WAV %s",cstr_input);
   input.OpenFile(cstr_input);
   LOGI("Open output WAV %s", cstr_output);
   output.NewFile(cstr_output);


  LOGI("Init Process");
   void* obj = ALGO_construct();

  LOGI("Run");
  while(!input.IsEOF()){
    input.ReadUnit(short_in,n_hop*n_channels);

    // short -> float
    for(int i=0;i<n_channels * n_hop; i++)
      buf_in[i] = static_cast<float>(short_in[i]/32768.0);
    ALGO_process_fp32(obj,buf_in,buf_out);

    // float -> short
    for(int i=0;i<n_channels * n_hop; i++)
      short_out[i] =  static_cast<short>(buf_out[i]*32768);
    output.Append(short_out,n_hop*n_channels);
  }

  LOGI("Release");
  ALGO_release(obj);
  input.Finish();
  output.Finish();
  delete[] short_in;
  delete[] short_out;
  delete[] buf_in;
  delete[] buf_out;

  env->ReleaseStringUTFChars(path_input, cstr_input);
  env->ReleaseStringUTFChars(path_output, cstr_output);

}