#pragma once

#include "rint.hpp"
#include <optional>
#include <utility>

namespace rpgmath {
    enum class token_type {ADD, SUB, MUL, DIV, NUM, RND};

    struct token {
    public:
        token_type type;
        std::optional<int> val;
        std::optional<rint> rnd;

        token(token_type type) : type(type), val(std::nullopt), rnd(std::nullopt) {}

        token(token_type type, int val) : type(type), val(val), rnd(std::nullopt) {} 

        token(token_type type, rint rnd) : type(type), val(std::nullopt), rnd(std::move(rnd)) {}
    };
}