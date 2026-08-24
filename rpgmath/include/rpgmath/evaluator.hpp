#pragma once

#include <vector>

#include "expression.hpp"

namespace rpgmath {

    class evaluator {
    public:
        rpgmath::roll_result evaluate(const rpgmath::expression& expression);
    private:
        int evalNode(const rpgmath::expression& expression, std::vector<int>& result);
    };

}