#include "evaluator.hpp"

#include <numeric> 

namespace rpgmath {
    roll_result evaluator::evaluate(const rpgmath::expression& expression) {
        std::vector<int> rolls = {};
        
        int total = evalNode(expression, rolls);

        return roll_result(total, rolls);
    }

    int evaluator::evalNode(const rpgmath::expression& expression, std::vector<int>& result) {
        const auto& token = expression.token;

        switch(token.type) {
            case token_type::NUM: return token.val.value();
            case token_type::RND: 
                auto res = token.rnd.value().roll();

                result.insert(result.end(), res.rolls.begin(), res.rolls.end());

                return res.total;
        } 

        int num1 = evalNode(*expression.left, result);
        int num2 = evalNode(*expression.right, result);

        switch(token.type) {
            case token_type::ADD: return num1 + num2;
            case token_type::SUB: return num1 - num2;
            case token_type::MUL: return num1 * num2;
            case token_type::DIV: return num1 / num2; 
        }

        return 0;
    }
}