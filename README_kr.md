[![Release](https://img.shields.io/github/v/release/uki7/korean-romanizer)](https://github.com/uki7/korean-romanizer/releases/latest)
[![MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

# korean-romanizer

korean-romanizer는 한국어를 로마자로 변환할 수 있는 C++ 라이브러리 입니다.

이 라이브러리는 [국립국어원 로마자 표기법](https://www.korean.go.kr/front/page/pageView.do?page_id=P000149&mn_id=99)을 사용합니다.
미래에 [매큔-라이샤워 표기법](https://ko.wikipedia.org/wiki/%EB%A7%A4%ED%81%94-%EB%9D%BC%EC%9D%B4%EC%83%A4%EC%9B%8C_%ED%91%9C%EA%B8%B0%EB%B2%95)
모드도 추가할 예정입니다.

## 소개

이 라이브리러에 관련이 있는 클래스들과 함수들은 모두 헤더 파일 `korean_romanizer.h` 통해서 접속하실 수 있습니다.
`korean_romanizer.h`와 `korean_romanizer.cpp` 파일들을 프로젝트 구조에 넣으신 후에 헤더 파일만 포함하시면 됩니다.

```c++
#include "korean_romanizer.h"
```

간단한 예제 파일은 ```test/test.cpp```에 찾으실 수 있습니다.

## 사용법

`korean_romanizer` 클래스에는 로마자로 변환된 `std::string`을 반환하는 함수가 포함돼 있습니다.

`korean_romanizer::romanize(std::string)`

다음과 같이 사용하실 수 있습니다:

```c++
std::string s = korean_romanizer::romanize("안녕하세요!");
std::cout << s;

// 콘솔에 "annyeonghaseyo!" 출력됨
```