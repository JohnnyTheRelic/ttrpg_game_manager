#include <ttrpg/user/User.hpp>
#include <stdexcept>

namespace ttrpg::user {
    User::User(const QString& username) {
        if (username.length() < 3 || username.length() > 32) {
            throw std::invalid_argument("Username must be between 3 and 16 characters long.");
        }
        this->username = username;
    }

    const QString& User::getUsername() const {
        return username;
    }
}