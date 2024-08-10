![Release](https://img.shields.io/github/v/release/uki7/korean-romanizer)
[![MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

# korean-romanizer

korean-romanizer is a small C++ library that converts
Hangul (written Korean) into its Latin script equivalent.

Currently, this library uses the [Revised Romanization of Korean system](https://www.korean.go.kr/front_eng/roman/roman_01.do)
developed by the National Institute of Korean Language. Support for the older [McCune-Reischauer system](https://en.wikipedia.org/wiki/McCune%E2%80%93Reischauer)
is planned.

## Introduction

All relevant classes and functions can be accessed through the header file `korean_romanizer.h`.
After inserting `korean_romanizer.h` and `korean_romanizer.cpp` into the project structure,
it can be included like the following:

```c++
#include "korean_romanizer.h"
```

A simple example file can be found at ```test/test.cpp``` in this repository.

## Usage

The class `korean_romanizer` contains a romanization function that returns a `std::string`:

`korean_romanizer::romanize(std::string)`

It can be used like the following:

```c++
std::string s = korean_romanizer::romanize("안녕하세요!");
std::cout << s;

// prints "annyeonghaseyo!"
```