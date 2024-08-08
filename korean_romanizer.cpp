#include <iostream>

namespace kr {
    struct korean_romanizer;
    struct korean_character {
        friend struct korean_romanizer;
    private:
        char c;
    protected:
        explicit korean_character(char _c);
    };
    korean_character::korean_character(const char _c) : c(_c) {}
    struct korean_romanizer {
        /// f
        enum romanization_mode {
            revised_romanization_of_korean,
            mccune_reischauer
        };
        /// returns the romanized string; the revised romanization of korean is the default romanization mode
        static std::string romanize(const std::string& s);
        /// returns the romanized string; the romanization mode can be manually set by the user
        static std::string romanize(const std::string& s, const romanization_mode& m);
    };
    std::string korean_romanizer::romanize(const std::string& s) {
        return romanize(s, romanization_mode::revised_romanization_of_korean);
    }
    std::string korean_romanizer::romanize(const std::string& s, const romanization_mode& m) {
        std::string result;
        return result;
    }
}

int main() {
    return 0;
}