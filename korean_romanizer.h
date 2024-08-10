#ifndef korean_romanizer_h
#define korean_romanizer_h

#include <string>

class korean_character {
    friend class korean_romanizer;
    /// the first hangul jamo representing a leading consonant in the unicode table: "ᄀ"
    int leading_consonant_jamo_min = 0x1100;
    /// the first hangul jamo representing a vowel in the unicode table: "ᅡ"
    int vowel_jamo_min = 0x1161;
    /// one code point before the first hangul jamo representing a trailing consonant in the unicode table: "ᆨ"
    int trailing_consonant_jamo_min = 0x11A7;
    /// the amount of hangul jamo representing a leading consonant
    int leading_consonant_jamo_count = 19;
    /// the amount of hangul jamo representing a vowel
    int vowel_jamo_count = 21;
    /// the amount of hangul jamo representing a trailing consonant, including the lack of one
    int trailing_consonant_jamo_count = 28;
    int vowel_and_trailing_consonant_jamo_combination_count = vowel_jamo_count * trailing_consonant_jamo_count;
    int all_jamo_combination_count = leading_consonant_jamo_count * vowel_and_trailing_consonant_jamo_combination_count;
    /// the first hangul syllable/character in the unicode table: "가"
    int character_min = 0xAC00;
    /// the leading consonant of the character
    int leading_consonant{};
    /// the vowel of the character
    int vowel{};
    /// the trailing consonant of the character
    int trailing_consonant{};
    /// the original character passed through the constructor
    wchar_t c{};
protected:
    /// if true, the character does not contain anything and is essentially null
    bool is_empty = false;
    /// if true, the character is a valid korean character and can be broken apart into its jamo components
    bool is_korean_character = true;
    struct leading_consonant_pronunciation {
        enum trailing_consonants { ㄱ, ㄲ, ㄳ, ㄴ, ㄵ, ㄶ, ㄷ, ㄹ, ㄺ, ㄻ, ㄼ, ㄽ, ㄾ, ㄿ, ㅀ, ㅁ, ㅂ, ㅄ, ㅅ, ㅆ, ㅇ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ };
        /// contains the default pronunciations for every leading consonant
        /// ㄱ, ㄲ, ㄴ, ㄷ, ㄸ, ㄹ, ㅁ, ㅂ, ㅃ, ㅅ, ㅆ, ㅇ, ㅈ, ㅉ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ in order according to their positions in the unicode block
        static std::string pronunciations[];
        static std::string get_pronunciation(int previous_trailing_consonant_index, int index);
    };
    struct vowel_pronunciation {
        /// contains the default pronunciations for every vowel
        /// ㅏ, ㅐ, ㅑ, ㅒ, ㅓ, ㅔ, ㅕ, ㅖ, ㅗ, ㅘ, ㅙ, ㅚ, ㅛ, ㅜ, ㅝ, ㅞ, ㅟ, ㅠ, ㅡ, ㅢ, ㅣ in order according to their positions in the unicode block
        static std::string pronunciations[];
        static std::string get_pronunciation(int index);
    };
    struct trailing_consonant_pronunciation {
        enum leading_consonants { ㄱ, ㄲ, ㄴ, ㄷ, ㄸ, ㄹ, ㅁ, ㅂ, ㅃ, ㅅ, ㅆ, ㅇ, ㅈ, ㅉ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ };
        /// contains the default pronunciations for every trailing consonant
        /// ㄱ, ㄲ, ㄳ, ㄴ, ㄵ, ㄶ, ㄷ, ㄹ, ㄺ, ㄻ, ㄼ, ㄽ, ㄾ, ㄿ, ㅀ, ㅁ, ㅂ, ㅄ, ㅅ, ㅆ, ㅇ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ in order according to their positions in the unicode block
        static std::string pronunciations[];
        static std::string get_pronunciation(int next_leading_consonant_index, int index);
    };
    explicit korean_character();
    explicit korean_character(wchar_t _c);
    /// decomposes a hangul syllable/character into its hangul jamo components
    void decompose_character(wchar_t _c);
    /// romanizes a hangul syllable/character
    std::string romanize_character(const korean_character& previous_character, const korean_character& next_character);
};
class korean_romanizer {
public:
    /// romanizes a hangul string using the revised romanization of korean system
    static std::string romanize(const std::string& s);
};
class korean_character;

#endif