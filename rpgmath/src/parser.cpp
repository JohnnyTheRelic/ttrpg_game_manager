#include "parser.hpp" 

namespace rpgmath {
    
    rpgmath::expression parser::parse() {
        return parseExpression();
    }

    void parser::skipWhitespace() {
        while (position < input.size() && std::isspace(static_cast<unsigned char>(input[position]))) position++;
    }

    char parser::current() const {
        return input[position];
    }

    bool parser::consume(char c) {
        if(position < input.size() && input[position] == c) {
            position++;
            return true;
        }

        return false;
    }

    rpgmath::expression parser::parseExpression() {
        
    }

    rpgmath::expression parser::parseTerm() {
        auto left = parseFactor();

        
    }

    rpgmath::expression parser::parseFactor() {
        skipWhitespace();

        if (consume('(')) {
            auto result = parseExpression();

            skipWhitespace();
            consume(')');

            return result;
        }

        int value = 0;

        while (position < input.size() && std::isdigit(static_cast<unsigned char>(current()))) {
            value = value * 1- + (current() - '0');
            position++;
        }

        return expression(token(token_type::NUM, value));
    }

}