#pragma once

#include "expression.hpp"
#include <string>
#include <cctype>

namespace rpgmath {
    class parser {
    public:
        explicit parser(const std::string& input) : input(input) {}

        rpgmath::expression parse();
    private:
        const std::string& input;
        std::size_t position = 0;

        void skipWhitespace();
        char current() const;
        bool consume(char c);

        rpgmath::expression parseExpression();
        rpgmath::expression parseTerm();
        rpgmath::expression parseFactor();
    };
}