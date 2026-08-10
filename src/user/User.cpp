#include <ttrpg/user/User.hpp>
#include <stdexcept>

namespace ttrpg::user {
    User::User(const std::string& username) {
        if (username.length() < 3 || username.length() > 16) {
            throw std::invalid_argument("Username must be between 3 and 16 characters long.");
        }
        this->username = username;
    }

    const std::string& User::getUsername() const {
        return username;
    }
}