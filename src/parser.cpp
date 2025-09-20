#include "parser.h"
#include <cctype>
#include <string>
#include <cstddef>

namespace {
    inline void trim(std::string& s) {
        std::size_t start = 0;
        while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;

        std::size_t end = s.size();
        while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

        if (start == 0 && end == s.size()) return;
        s.assign(s.begin() + static_cast<std::ptrdiff_t>(start),
                 s.begin() + static_cast<std::ptrdiff_t>(end));
    }

    inline void normalize_spaces(std::string& s) {
        std::string out;
        out.reserve(s.size());
        bool prevSpace = false;
        for (unsigned char ch : s) {
            bool isSpace = std::isspace(ch);
            if (isSpace) {
                if (!prevSpace) out.push_back(' ');
            } else {
                out.push_back(static_cast<char>(ch));
            }
            prevSpace = isSpace;
        }
        s.swap(out);
    }
}

namespace StringUtils {

    void parseName(const std::string& fullName,
                   std::string* firstName,
                   std::string* lastName)
    {
        if (firstName) *firstName = "";
        if (lastName)  *lastName  = "";

        std::string s = fullName;
        trim(s);
        normalize_spaces(s);
        trim(s);

        std::size_t pos = s.find(' ');
        if (pos == std::string::npos) {
            if (firstName) *firstName = s;
            return;
        }

        if (firstName) *firstName = s.substr(0, pos);
        if (lastName)  *lastName  = (pos + 1 < s.size()) ? s.substr(pos + 1) : "";
    }

    std::string getUsername(const std::string& email) {
        const std::size_t at = email.find('@');
        return (at == std::string::npos) ? email : email.substr(0, at);
    }
}
