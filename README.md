# template_export

배포용 라이브러리 작업 템플릿  

wrapper 선언 헤더, 알고리즘 dll, 예제 코드, 문서 만을 package에 담아서 공유함.  

## 파일 구성  
+ algo.h  : (외부 공유) C에서 호출 가능한(및 다른 언어) wrapper 함수 선언만을 담고 있다. 
+ src/algo_decl.h : (개발 전용) 알고리즘 class가 선언되는 헤더 파일.
+ src/algo_impl.cpp : (개발 전용) 알고리즘 class의 정의가 있는 소스 코드.
+ src/algo_wrapper.cpp : (개발 전용) wrapper 함수의 정의가 있는 소스 코드.   

## CMake copy
cmake 스크립트에서  
wrapper 선언 헤더, 알고리즘 dll, 예제 코드, 문서를 ```cmake``` 수행시 package로 복사하게 되어있음. 



## 프로젝트 구성  
cmake로 솔루션 생성 시, 알고리즘 프로젝트와 테스트 프로젝트 2개가 같이 있게 됨.  
솔루션 빌드를 하게 되면 라이브러리 빌드와 테스트 프로젝트 빌드를 동시에 수행.  
테스트 프로젝트를 시작 프로젝트로 설정하고 디버깅을 진행. 

---

make로 생성 시에는 라이브러리와 test코드 실행 파일이 같이 생성.  

---
*여기까지의 내용은 배포시 삭제.
*마이크 입출력 package는 작업 해야함.

# ALGO

## 요구사항  
[CMake](https://cmake.org/download/)      

## 사용법
```test.cpp```와 ```CMakeLists.txt``` 참고.  


  
## test코드 빌드
+ Windows
```
<bin 폴더에서>
cmake ..
```
시 비주얼스튜디오 솔루션이 생성됩니다.   

비주얼 스튜디오 실행 후  
시작프로젝트를 ```...```으로 설정합니다. 
```Release``` 또는 ```RelwithDebInfo``` 모드로만 라이브러리를 사용할 수 있습니다.   
