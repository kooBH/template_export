
# Package Rust

C++ 라이브러리(MYLIB.dll)를 Rust에서 호출하기 위한 FFI(Foreign Function Interface) 구현 예제.


```
package_rust/
├── Cargo.toml            # 프로젝트 설정 및 의존성 관리
├── build.rs              # C++ 라이브러리(.lib) 링킹 및 DLL 자동 복사 스크립트
├── .gitignore            # Rust 빌드 결과물 및 임시 파일 제외 설정
├── lib/                 # 외부 라이브러리 원본 보관 폴더
│   ├── MYLIB.lib         # 컴파일 타임 링킹용 라이브러리
│   └── MYLIB.dll         # 런타임 실행용 동적 라이브러리 -> 빌드시 target 폴더로 복사
└── src/
    └── main.rs           # FFI 선언 및 AlgoEngine 래퍼 구현
```