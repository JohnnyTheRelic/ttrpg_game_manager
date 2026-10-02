#include <ttrpg/user/User.hpp>
#include <stdexcept>

namespace ttrpg::user {
User::User(const QString& username) : username(std::move(username)) {
        if (username.length() < 3 || username.length() > 32) {
            throw std::invalid_argument("Username must be between 3 and 16 characters long.");
        }
    }

    const QString& User::getUsername() const noexcept {
        return username;
    }
}