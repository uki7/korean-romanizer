[![Release](https://img.shields.io/github/v/release/uki7/korean-romanizer)](https://github.com/uki7/korean-romanizer/releases/latest)
[![MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

# korean-romanizer

korean-romanizer is a small C++ library that converts
Hangul (written Korean) into its Latin script equivalent.

Currently, this library uses the [Revised Romanization of Korean system](https://www.korean.go.kr/front_eng/roman/roman_01.do)
developed by the National Institute of Korean Language. Support for the older [McCune-Reischauer system](https://en.wikipedia.org/wiki/McCune%E2%80%93Reischauer)
is planned.

## Introduction

All relevant classes and functions are defined in the header file `korean_romanizer.h`.
After adding the files `korean_romanizer.h` and `korean_romanizer.cpp` into the project structure,
it can be included like the following:

```c++
#include "korean_romanizer.h"
```

A simple example file can be found at ```test/test.cpp``` in this repository.

## Usage

The `korean_romanizer` class contains a romanization function called `romanize` that takes a `std::string` and returns a `std::string`.

It can be accessed and used like the following:

```c++
std::string s = korean_romanizer::romanize("안녕하세요!");
std::cout << s;

// prints "annyeonghaseyo!"
```

## Limitations

Korean is a difficult language to romanize programmatically due to many pronunciation inconsistencies.
This library attemps to resolve most of these inconsistencies, but some discrepancies may be completely unavoidable.

One of these discrepancies is when the same instance of a trailing consonant (e.g. "ㄴ") into a leading consonant (e.g. "ㄹ") yields different pronunciations (and thus, romanizations):

| Written | Pronunciation | Romanization |
|---------|---------------|--------------|
| 난로      | 날로            | Na**ll**o
| 신문로     | 신문노           | Sinmu**nn**o

As implementing a more complicated system could bloat the size and limit the speed of this library considerably, this library unfortunately does not respect this pronunciation discrepancy,
opting for the more common pronunciation instead:

```c++
std::cout << korean_romanizer::romanize("난로");
// prints "nallo"
std::cout << korean_romanizer::romanize("신문로");
// prints "sinmullo"
```