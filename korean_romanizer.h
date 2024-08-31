#ifndef korean_romanizer_h
#define korean_romanizer_h

#include <string>

/**
 * @brief Encapsulates a Hangul character, providing functionality for decomposition and romanization.
 */
class korean_character {
    friend class korean_romanizer;
    /**
     * The code point of the first Hangul jamo representing a leading consonant (ᄀ) in the Unicode character table.
     *
     * @see <a href="https://en.wikipedia.org/wiki/Hangul_Jamo_(Unicode_block)">Hangul Jamo (Unicode block) on Wikipedia.</a>
     */
    int leading_consonant_jamo_min = 0x1100;
    /**
     * The code point of the first Hangul jamo representing a vowel (ᅡ) in the Unicode character table.
     *
     * @see <a href="https://en.wikipedia.org/wiki/Hangul_Jamo_(Unicode_block)">Hangul Jamo (Unicode block) on Wikipedia.</a>
     */
    int vowel_jamo_min = 0x1161;
    /**
     * One code point before the first Hangul jamo representing a trailing consonant (ᆨ) in the Unicode character table.
     * (Moving the code point accounts for the lack of a trailing consonant.)
     *
     * @see <a href="https://en.wikipedia.org/wiki/Hangul_Jamo_(Unicode_block)">Hangul Jamo (Unicode block) on Wikipedia.</a>
     */
    int trailing_consonant_jamo_min = 0x11A7;
    /**
     * The amount of Hangul jamo representing a leading consonant.
     */
    int leading_consonant_jamo_count = 19;
    /**
     * The amount of Hangul jamo representing a vowel.
     */
    int vowel_jamo_count = 21;
    /**
     * The amount of Hangul jamo representing a trailing consonant, including the lack thereof.
     */
    int trailing_consonant_jamo_count = 28;
    /**
     * The product of @link vowel_jamo_count @endlink and @link trailing_consonant_jamo_count @endlink.
     *
     * This value is used in the decomposition algorithm of @link decompose_character @endlink.
     */
    int vowel_and_trailing_consonant_jamo_combination_count = vowel_jamo_count * trailing_consonant_jamo_count;
    /**
     * The product of @link leading_consonant_jamo_count @endlink and @link vowel_and_trailing_consonant_jamo_combination_count @endlink,
     * representing the total amount of Hangul jamo combinations.
     *
     * This value is used in the decomposition algorithm of @link decompose_character @endlink.
     */
    int all_jamo_combination_count = leading_consonant_jamo_count * vowel_and_trailing_consonant_jamo_combination_count;
    /**
     * The code point of the first Hangul character (가) in the Unicode character table.
     *
     * @see <a href="https://en.wikipedia.org/wiki/Hangul_Syllables">Hangul Syllables on Wikipedia.</a>
     */
    int character_min = 0xAC00;
    /**
     * The leading consonant of this @link korean_character @endlink instance.
     */
    int leading_consonant{};
    /**
     * The vowel of this @link korean_character @endlink instance.
     */
    int vowel{};
    /**
     * The trailing consonant of this @link korean_character @endlink instance.
     */
    int trailing_consonant{};
    /**
     * The original character passed through the constructor.
     */
    wchar_t c{};
protected:
    /**
     * If <code>true</code>, this @link korean_character @endlink instance does not contain anything and is essentially <code>null</code>.
     */
    bool is_empty = false;
    /**
     * If <code>true</code>, this @link korean_character @endlink instance is a valid Hangul character and can be broken apart into its jamo components.
     */
    bool is_korean_character = true;
    /**
     * @brief Romanizes the leading consonant of a @link korean_character @endlink instance.
     * @details Romanizes the leading consonant of a @link korean_character @endlink instance while taking into account the preceding character's trailing consonant.
     */
    struct leading_consonant_pronunciation {
       /**
        * Contains every trailing consonant for readability purposes when parsing the preceding character's trailing consonant in @link get_pronunciation @endlink.
        */
        enum trailing_consonants { ㄱ, ㄲ, ㄳ, ㄴ, ㄵ, ㄶ, ㄷ, ㄹ, ㄺ, ㄻ, ㄼ, ㄽ, ㄾ, ㄿ, ㅀ, ㅁ, ㅂ, ㅄ, ㅅ, ㅆ, ㅇ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ };
        /**
         * Contains the default pronunciation for every possible leading consonant.
         *
         * Ordered according to their positions in the Unicode character table, which is
         * ㄱ, ㄲ, ㄴ, ㄷ, ㄸ, ㄹ, ㅁ, ㅂ, ㅃ, ㅅ, ㅆ, ㅇ, ㅈ, ㅉ, ㅊ, ㅋ, ㅌ, ㅍ, and ㅎ.
         */
        static std::string pronunciations[];
        /**
         * Romanizes the leading consonant given the preceding character's trailing consonant.
         * @param previous_trailing_consonant_index The pronunciations index of the preceding character's trailing consonant.
         * @param index The pronunciations index of the leading consonant.
         * @return The romanization of the leading consonant.
         */
        static std::string get_pronunciation(int previous_trailing_consonant_index, int index);
    };
    /**
     * @brief Romanizes the vowel of a @link korean_character @endlink instance.
     */
    struct vowel_pronunciation {
        /**
         * Contains the default pronunciation for every possible vowel.
         *
         * Ordered according to their positions in the Unicode character table, which is
         * ㅏ, ㅐ, ㅑ, ㅒ, ㅓ, ㅔ, ㅕ, ㅖ, ㅗ, ㅘ, ㅙ, ㅚ, ㅛ, ㅜ, ㅝ, ㅞ, ㅟ, ㅠ, ㅡ, ㅢ, and ㅣ.
         */
        static std::string pronunciations[];
        /**
         * Romanizes the vowel.
         * @param index The pronunciations index of the vowel.
         * @return The romanization of the vowel.
         */
        static std::string get_pronunciation(int index);
    };
    /**
     * @brief Romanizes the trailing consonant of a @link korean_character @endlink instance.
     * @details Romanizes the trailing consonant of a @link korean_character @endlink instance while taking into account the following character's leading consonant.
     */
    struct trailing_consonant_pronunciation {
       /**
        * Contains every leading consonant for readability purposes when parsing the following character's leading consonant in @link get_pronunciation @endlink.
        */
        enum leading_consonants { ㄱ, ㄲ, ㄴ, ㄷ, ㄸ, ㄹ, ㅁ, ㅂ, ㅃ, ㅅ, ㅆ, ㅇ, ㅈ, ㅉ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ };
        /**
         * Contains the default pronunciation for every possible trailing consonant.
         *
         * Ordered according to their positions in the Unicode character table, which is
         * ㄱ, ㄲ, ㄳ, ㄴ, ㄵ, ㄶ, ㄷ, ㄹ, ㄺ, ㄻ, ㄼ, ㄽ, ㄾ, ㄿ, ㅀ, ㅁ, ㅂ, ㅄ, ㅅ, ㅆ, ㅇ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, and ㅎ.
         */
        static std::string pronunciations[];
        /**
         * Romanizes the trailing consonant given the following character's leading consonant.
         * @param next_leading_consonant_index The pronunciations index of the following character's leading consonant.
         * @param index The pronunciations index of the trailing consonant.
         * @return The romanization of the trailing consonant.
         */
        static std::string get_pronunciation(int next_leading_consonant_index, int index);
    };
    /**
     * Creates an empty instance of @link korean_character @endlink.
     *
     * @see @link is_empty @endlink
     */
    explicit korean_character();
    /**
     * Creates an instance of @link korean_character @endlink with the given character.
     *
     * @param _c A character.
     */
    explicit korean_character(wchar_t _c);
    /**
     * Decomposes a Hangul character into its jamo components, assigning them to the variables
     * @link leading_consonant @endlink, @link vowel @endlink, and @link trailing_consonant @endlink.
     *
     * For the decomposition algorithm, please reference Section 3.12 of the Unicode Standard linked below.
     *
     * @param _c The Hangul character to be decomposed into its jamo components.
     * @see <a href="https://en.wikipedia.org/wiki/Hangul_Jamo_(Unicode_block)">Section 3.12 of the Unicode Standard.</a>
     */
    void decompose_character(wchar_t _c);
    /**
     * Romanizes a Hangul character given its surrounding characters.
     *
     * @param previous_character The character preceding the current character.
     * @param next_character The character following the current character.
     * @return The romanization of the Hangul character.
     */
    std::string romanize_character(const korean_character& previous_character, const korean_character& next_character);
};
/**
 * @brief Provides functionality for romanizing a Hangul string.
 */
class korean_romanizer {
public:
 /**
  * Romanizes a Hangul string using the Revised Romanization of Korean system while leaving non-Hangul and incomplete Hangul characters untouched.
  *
  * @param s The Hangul string to be romanized.
  * @return The romanization of the Hangul string.
  */
 static std::string romanize(const std::string& s);
};

#endif