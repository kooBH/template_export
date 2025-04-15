# Android Lib

apk 빌드를 하고 생성된
```app-debug.apk```을 압축해제 한 다음. 

lib 폴더 안의
```arm64-v8a```,```armeabi-v7a```,```x86```,```x86_64```폴더를 를 

```main/cpp/CS/jni``` 에 넣기.  

+ 참고

```cmake
set (CS_LIBS ${CMAKE_CURRENT_LIST_DIR}/CS/jni/${ANDROID_ABI})
LINK_DIRECTORIES(CS_LIBS)
add_library( CS SHARED IMPORTED )
set_target_properties(CS PROPERTIES IMPORTED_LOCATION ${CS_LIBS}/libClearSenseProcessor.so )
```
이렇게 경로 구성이 되어있음.  
