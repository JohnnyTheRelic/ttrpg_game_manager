#pragma once

#include <vector>

namespace rpgmath {
    struct roll_result {
        int total;
        std::vector<int> rolls;

        roll_result(int total, std::vector<int> rolls) : total(total), rolls(rolls) {}
    };
}
