#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

namespace kr {
    struct korean_romanizer;
    struct korean_character {
        friend struct korean_romanizer;
    private:
        int leading_consonant_jamo_min = 0x1100;
        int vowel_jamo_min = 0x1161;
        int trailing_consonant_jamo_min = 0x11A7;
        int leading_consonant_jamo_count = 19;
        int vowel_jamo_count = 21;
        int trailing_consonant_jamo_count = 28;
        int vowel_and_trailing_consonant_jamo_combination_count = vowel_jamo_count * trailing_consonant_jamo_count;
        int all_jamo_combination_count = leading_consonant_jamo_count * vowel_and_trailing_consonant_jamo_combination_count;
        int syllable_min = 0xAC00;
        int syllable_max = 0xD7A3;
        int leading_consonant;
        int vowel;
        int trailing_consonant;
        wchar_t c;
    protected:
        bool is_empty = false;
        bool is_korean_character = true;
        struct leading_consonant_pronunciation {
            enum trailing_consonants { ㄱ, ㄲ, ㄳ, ㄴ, ㄵ, ㄶ, ㄷ, ㄹ, ㄺ, ㄻ, ㄼ, ㄽ, ㄾ, ㄿ, ㅀ, ㅁ, ㅂ, ㅄ, ㅅ, ㅆ, ㅇ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ };
            std::string pronunciations[19] = {"g", "kk", "n", "d", "tt", "r", "m", "b", "pp", "s", "ss", "", "j", "jj", "ch", "k", "t", "p", "h"};
            std::string get_pronunciation(int previous_trailing_consonant_index, int index);
        };
        struct vowel_pronunciation {
            std::string pronunciations[22] = {"a", "ae", "ya", "yae", "eo", "e", "yeo", "ye", "o", "wa", "wae", "oe", "yo", "u", "wo", "we", "wi", "yu", "eu", "ui", "i"};
            std::string get_pronunciation(int index);
        };
        struct trailing_consonant_pronunciation {
            enum leading_consonants { ㄱ, ㄲ, ㄴ, ㄷ, ㄸ, ㄹ, ㅁ, ㅂ, ㅃ, ㅅ, ㅆ, ㅇ, ㅈ, ㅉ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ };
            std::string pronunciations[27] = {"k", "k", "k", "n", "n", "n", "d", "l", "k", "m", "l", "l", "l", "l", "l", "m", "p", "p", "t", "t", "ng", "t", "t", "k", "t", "p", "t"};
            std::string get_pronunciation(int next_leading_consonant_index, int index);
        };
        explicit korean_character();
        explicit korean_character(wchar_t _c);
        void decompose_character(wchar_t _c);
        std::string romanize_character(const korean_character& previous_character, const korean_character& next_character);
    };
    std::string korean_character::leading_consonant_pronunciation::get_pronunciation(int previous_trailing_consonant_index, int index) {
        if (index < 0) {
            return "";
        }
        switch (index) {
            // ㄱ
            case 0:
                switch (previous_trailing_consonant_index) {
                    case ㄺ:
                    case ㄻ:
                    case ㄼ:
                    case ㄽ:
                    case ㄾ:
                    case ㄿ:
                    case ㅀ:
                    case ㅎ: return "k";
                    default: return pronunciations[index];
                }
            // ㄴ
            case 2:
                switch (previous_trailing_consonant_index) {
                    case ㄹ:
                    case ㅀ: return "l";
                    default: return pronunciations[index];
                }
            // ㄷ
            case 3:
                switch (previous_trailing_consonant_index) {
                    case ㄾ:
                    case ㄶ:
                    case ㅎ: return "t";
                    default: return pronunciations[index];
                }
            // ㄹ
            case 5:
                switch (previous_trailing_consonant_index) {
                    case ㄱ:
                    case ㄲ:
                    case ㄳ:
                    case ㄺ:
                    case ㄼ:
                    case ㄿ:
                    case ㅁ:
                    case ㅂ:
                    case ㅄ:
                    case ㅇ:
                    case ㅋ:
                    case ㅍ: return "n";
                    case ㄴ: case ㄵ:
                    case ㄶ:
                    case ㄷ:
                    case ㄹ:
                    case ㄻ:
                    case ㄽ:
                    case ㄾ:
                    case ㅀ:
                    case ㅅ:
                    case ㅆ:
                    case ㅈ:
                    case ㅊ:
                    case ㅌ:
                    case ㅎ: return "l";
                    default: return pronunciations[index];
                }
            // ㅇ
            case 11:
                switch (previous_trailing_consonant_index) {
                    case ㄱ: return "n";
                    case ㄺ: return "g";
                    case ㄲ: return "kk";
                    case ㄳ:
                    case ㄽ:
                    case ㅄ:
                    case ㅅ: return "s";
                    case ㅇ:
                    case ㄴ:
                    case ㄶ: return "n";
                    case ㄷ:
                    case ㄵ:
                    case ㅈ: return "j";
                    case ㄹ:
                    case ㅀ: return "l";
                    case ㄻ:
                    case ㅁ: return "m";
                    case ㄼ:
                    case ㅂ: return "b";
                    case ㄾ:
                    case ㅌ: return "ch";
                    case ㅆ: return "ss";
                    case ㅊ: return "ch";
                    case ㅋ: return "k";
                    case ㄿ:
                    case ㅍ: return "p";
                    default: return pronunciations[index];
                }
            // ㅈ
            case 12:
                switch (previous_trailing_consonant_index) {
                    case ㅎ: return "ch";
                    default: return pronunciations[index];
                }
            // ㅉ, ㅊ, ㅋ, ㅌ
            case 13:
            case 14:
            case 15:
            case 16:
                switch (previous_trailing_consonant_index) {
                    case ㅈ:
                    case ㅊ: return "ch";
                    default: return pronunciations[index];
                }
            // ㅎ
            case 18:
                switch (previous_trailing_consonant_index) {
                    case ㄲ: return "kk";
                    case ㄷ:
                    case ㄾ:
                    case ㅅ:
                    case ㅆ:
                    case ㅈ:
                    case ㅊ:
                    case ㅌ: return "ch";
                    case ㄺ: return "k";
                    case ㄼ: return "p";
                    case ㄽ: return "s";
                    case ㅀ: return "r";
                    default: return pronunciations[index];
                }
            default: return pronunciations[index];
        }
    }
    std::string korean_character::vowel_pronunciation::get_pronunciation(int index) {
        if (index < 0) {
            return "";
        }
        return pronunciations[index];
    }
    std::string korean_character::trailing_consonant_pronunciation::get_pronunciation(int next_leading_consonant_index, int index) {
        if (index < 0) {
            return "";
        }
        switch (index) {
            // ㄱ
            case 0:
                switch (next_leading_consonant_index) {
                    case ㄲ:
                    case ㅋ: return "";
                    case ㅇ:;
                    case ㄴ:
                    case ㅁ:
                    case ㄹ: return "ng";
                    default: return pronunciations[index];
                }
            // ㄲ
            case 1:
                switch (next_leading_consonant_index) {
                    case ㄲ:
                    case ㅇ:
                    case ㅋ:
                    case ㅎ: return "";
                    case ㄴ:
                    case ㅁ:
                    case ㄹ: return "ng";
                    default: return pronunciations[index];
                }
            // ㄳ
            case 2:
                switch (next_leading_consonant_index) {
                    case ㄲ:
                    case ㅋ: return "";
                    case ㄴ:
                    case ㅁ:
                    case ㄹ: return "ng";
                    default: return pronunciations[index];
                }
            // ㄴ
            case 3:
                switch (next_leading_consonant_index) {
                    case ㅇ: return "";
                    default: return pronunciations[index];
                }
            // ㄷ
            case 6:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㅁ: return "n";
                    case ㄹ: return "l";
                    case ㄸ:
                    case ㅇ:
                    case ㅌ:
                    case ㅎ: return "";
                    default: return pronunciations[index];
                }
            // ㄹ
            case 7:
                switch (next_leading_consonant_index) {
                    case ㅇ: return "";
                    default: return pronunciations[index];
                }
            // ㄺ
            case 8:
                switch (next_leading_consonant_index) {
                    case ㄱ:
                    case ㄲ:
                    case ㅇ:
                    case ㅎ: return "l";
                    case ㄴ:
                    case ㄹ:
                    case ㅁ: return "ng";
                    default: return pronunciations[index];
                }
            // ㄻ
            case 9:
                switch (next_leading_consonant_index) {
                    case ㄹ:
                    case ㅁ:
                    case ㅇ: return "l";
                    default: return pronunciations[index];
                }
            // ㄼ
            case 10:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㄹ: return "m";
                    case ㄷ:
                    case ㄸ:
                    case ㅂ:
                    case ㅅ:
                    case ㅆ:
                    case ㅈ:
                    case ㅉ:
                    case ㅊ:
                    case ㅋ:
                    case ㅌ:
                    case ㅎ: return "p";
                    case ㅃ: return "";
                    default: return pronunciations[index];
                }
            // ㄿ
            case 13:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㄹ: return "m";
                    case ㄷ:
                    case ㄸ:
                    case ㅂ:
                    case ㅅ:
                    case ㅆ:
                    case ㅈ:
                    case ㅉ:
                    case ㅊ:
                    case ㅋ:
                    case ㅌ:
                    case ㅎ: return "p";
                    case ㅃ:
                    case ㅍ: return "";
                    default: return pronunciations[index];
                }
            // ㅀ
            case 14:
                switch (next_leading_consonant_index) {
                    case ㅎ:
                    case ㅇ: return "";
                    default: return pronunciations[index];
                }
            // ㅁ
            case 15:
                switch (next_leading_consonant_index) {
                    case ㅇ: return "";
                    default: return pronunciations[index];
                }
            // ㅂ
            case 16:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㄹ:
                    case ㅁ: return "m";
                    case ㅃ:
                    case ㅇ:
                    case ㅎ: return "";
                    default: return pronunciations[index];
                }
            // ㅄ
            case 17:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㄹ:
                    case ㅁ: return "m";
                    case ㅃ: return "";
                    default: return pronunciations[index];
                }
            // ㅅ, ㅆ, ㅈ, ㅊ
            case 18:
            case 19:
            case 21:
            case 22:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㅁ: return "n";
                    case ㄹ: return "l";
                    case ㄸ:
                    case ㅇ:
                    case ㅌ:
                    case ㅎ: return "";
                    default: return pronunciations[index];
                }
            // ㅋ
            case 23:
                switch (next_leading_consonant_index) {
                    case ㄲ:
                    case ㅇ: return "";
                    case ㄴ:
                    case ㅁ:
                    case ㄹ: return "ng";
                    default: return pronunciations[index];
                }
            // ㅌ
            case 24:
                switch (next_leading_consonant_index) {
                    case ㄴ:
                    case ㅁ: return "n";
                    case ㄸ:
                    case ㅇ:
                    case ㅎ: return "";
                    case ㄹ: return "l";
                    default: return pronunciations[index];
                }
            // ㅍ
            case 25:
                switch (next_leading_consonant_index) {
                    case ㅃ:
                    case ㅇ: return "";
                    default: return pronunciations[index];
                }
            // ㅎ
            case 26:
                switch (next_leading_consonant_index) {
                    case ㄱ:
                    case ㄲ:
                    case ㄷ:
                    case ㄸ:
                    case ㅇ:
                    case ㅈ:
                    case ㅉ:
                    case ㅊ:
                    case ㅋ:
                    case ㅌ:
                    case ㅍ:
                    case ㅎ: return "";
                    case ㄴ:
                    case ㅁ:
                    case ㄹ: return "n";
                    default: return pronunciations[index];
                }
            default: return pronunciations[index];
        }
    }
    korean_character::korean_character() {
        is_empty = true;
    }
    korean_character::korean_character(const wchar_t _c) : c(_c) {
        decompose_character(c);
    }
    void korean_character::decompose_character(const wchar_t _c) {
        const int i = _c - syllable_min;
        if (i < 0 || i >= all_jamo_combination_count)
            is_korean_character = false;
        std::string s;
        const int _leading_consonant = leading_consonant_jamo_min + (i / vowel_and_trailing_consonant_jamo_combination_count);
        const int _vowel = vowel_jamo_min + (i % vowel_and_trailing_consonant_jamo_combination_count) / trailing_consonant_jamo_count;
        const int _trailing_consonant = trailing_consonant_jamo_min + (i % trailing_consonant_jamo_count);
        leading_consonant = _leading_consonant;
        vowel = _vowel;
        if (_trailing_consonant != trailing_consonant_jamo_min)
            trailing_consonant = _trailing_consonant;
        else
            trailing_consonant = 0;
    }
    std::string korean_character::romanize_character(const korean_character& previous_character, const korean_character& next_character) {
        if (!is_korean_character)
            return {1, c};
        int leading_consonant_index = leading_consonant - leading_consonant_jamo_min;
        int vowel_index = vowel - vowel_jamo_min;
        int trailing_consonant_index = trailing_consonant - (trailing_consonant_jamo_min + 1);
        leading_consonant_pronunciation l;
        vowel_pronunciation v;
        trailing_consonant_pronunciation t;
        int previous_trailing_consonant_index;
        if (!previous_character.is_empty)
            previous_trailing_consonant_index = previous_character.trailing_consonant - (trailing_consonant_jamo_min + 1);
        else
            previous_trailing_consonant_index = -1;
        int next_leading_consonant_index;
        if (!next_character.is_empty)
            next_leading_consonant_index = next_character.leading_consonant - leading_consonant_jamo_min;
        else
            next_leading_consonant_index = -1;
        std::string s;
        s += l.get_pronunciation(previous_trailing_consonant_index, leading_consonant_index);
        s += v.get_pronunciation(vowel_index);
        s += t.get_pronunciation(next_leading_consonant_index, trailing_consonant_index);
        return s;
    }
    struct korean_romanizer {
        enum romanization_mode {
            revised_romanization_of_korean,
            mccune_reischauer
        };
        static std::string romanize(const std::string& s);
        static std::string romanize(const std::string& s, const romanization_mode& m);
    };
    std::string korean_romanizer::romanize(const std::string& s) {
        return romanize(s, revised_romanization_of_korean);
    }
    std::string korean_romanizer::romanize(const std::string& s, const romanization_mode& m) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring w = converter.from_bytes(s);
        const wchar_t *_w = w.c_str();
        std::string result;
        korean_character previous_character;
        korean_character current_character = korean_character();
        korean_character next_character;
        for (int i = 0; i < w.size(); ++i) {
            previous_character = current_character;
            current_character = korean_character(_w[i]);
            next_character = i < w.size() - 1 ? korean_character(_w[i + 1]) : korean_character();
            if (current_character.is_korean_character) {
                std::string pronunciation = current_character.romanize_character(previous_character, next_character);
                result += pronunciation;
            } else {
                result += current_character.c;
            }
        }
        return result;
    }
}

int main() {
    std::cout << kr::korean_romanizer::romanize("") << std::endl;
    return 0;
}