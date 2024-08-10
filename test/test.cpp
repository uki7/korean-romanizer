#include <iostream>

#include "korean_romanizer.h";

int main() {
    std::cout << korean_romanizer::romanize("안녕하세요!");
    return 0;
}