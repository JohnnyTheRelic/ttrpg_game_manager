#pragma once

#include <string>

namespace ttrpg::user {
    class User {
    public:
        explicit User(const std::string& username);

        const std::string& getUsername() const;

    private:
        std::string username;
    };
}