# template_export

배포용 라이브러리 작업 템플릿  

wrapper 선언 헤더, 알고리즘 dll, 예제 코드, 문서 만을 package에 담아서 공유함.  

## 파일 구성  
+ ALGO.h  : (외부 공유) C에서 호출 가능한(및 다른 언어) wrapper 함수 선언만을 담고 있다. 
+ src/ALGO_decl.h : (개발 전용) 알고리즘 class가 선언되는 헤더 파일.
+ src/ALGO_impl.cpp : (개발 전용) 알고리즘 class의 정의가 있는 소스 코드.
+ src/ALGO_wrapper.cpp : (개발 전용) wrapper 함수의 정의가 있는 소스 코드.   

## ALGO 포팅 시 주의 사항
- ```min```,```max```,```swap``` 등의 매크로 함수가 충돌하기 때문에, ```MPMIN```, ```MPMAX```. ```MPSWAP``` 등으로 변경해서 사용.  
- MSVC에서는 ```string.h```를 include 하지 않아도 ```memset```이 되지만 다른 컴파일러는 아닌 경우가 있으므로, ```#include <string.h>```를 넣어줘야함.  
- ```abs```같은 기본 math 함수들이 MSVC에서는 타입별로 오버로딩이 되어있지만, 다른 컴파일러에서는 아닌 경우가 있으므로, ```fabsf```등으로 타입에 맞게 변경해서 사용.  
- 그외에도 오버로딩 미구현 및 매크로 충돌로 인한 문제가 있을 수 있기 때문에 확인 필요. 

## CMake copy
cmake 스크립트에서  
wrapper 선언 헤더, 알고리즘 dll, 예제 코드, 문서를 ```cmake``` 수행시 package로 복사하게 되어있음. 

## 프로젝트 구성  
cmake로 솔루션 생성 시, 알고리즘 프로젝트와 테스트 프로젝트 2개가 같이 있게 됨.  
솔루션 빌드를 하게 되면 라이브러리 빌드와 테스트 프로젝트 빌드를 동시에 수행.  
테스트 프로젝트를 시작 프로젝트로 설정하고 디버깅을 진행. 

---

make로 생성 시에는 라이브러리와 test코드 실행 파일이 같이 생성.  

## python package  
+ ALGO.py 로 ctype을 래핑해서 라이브러리의 알고리즘 호출  
+ test_File_IO.py에서 data 폴더의 파일을 읽어서 처리함.  
+ test_Mic_IO.py에서 마이크 입력을 받아서 처리함.  

---

## Apple
- Apple 장비의 경우는 별도의 플래그로 지정을 해줘야 runtime path에서 의존성 라이브러리를 찾음(있는 경우) -> ```CMakeListst.txt``` 의 ```@rpath``` 관련 부분

---

*여기까지의 내용은 배포시 삭제  
*TODO : 마이크 입출력 C++package  

# ALGO

## 요구사항  
- [CMake](https://cmake.org/download/)
- Submodule update
```
git submodule init
git submodule update
```

## 사용법
```test.cpp```와 ```CMakeLists.txt``` 참고.  


  
## test코드 빌드
+ Windows
```
<build 폴더에서>
cmake ..
```
시 비주얼스튜디오 솔루션이 생성됩니다.   

비주얼 스튜디오 실행 후  
시작프로젝트를 ```...```으로 설정합니다. 
```Release``` 또는 ```RelwithDebInfo``` 모드로만 라이브러리를 사용할 수 있습니다.   
