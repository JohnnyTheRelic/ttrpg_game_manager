#include "rint.hpp"

namespace rpgmath {
    rint::rint(int mult, int die) {
        this->mult = mult;
        this->die = die;
    }

    rpgmath::roll_result rint::roll() const {
        std::vector<int> dice(mult, 0);

        std::random_device rd;

        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dist(1, die);

        int total = 0;
        for(size_t i = {}; i < mult; ++i) {
            dice[i] = dist(gen);
            total += dice[i];
        }

        return roll_result(total, dice);
    }
}