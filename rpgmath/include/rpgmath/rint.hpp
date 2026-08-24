#pragma once

#include "roll_result.hpp"

#include <random>
#include <vector>

namespace rpgmath {
    class rint {
    public: 
        rint(int mult, int die);

        rpgmath::roll_result roll() const;
    private:
        int mult;
        int die;
    };
}