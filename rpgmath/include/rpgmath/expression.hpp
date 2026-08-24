#pragma once

#include "token.hpp"
#include <memory>

namespace rpgmath {
    struct expression {
        rpgmath::token token;
        std::unique_ptr<expression> left;
        std::unique_ptr<expression> right;

        expression(rpgmath::token token) : token(token) {}       
    };
}