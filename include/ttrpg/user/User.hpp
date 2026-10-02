#pragma once

#include <QString>

namespace ttrpg::user {
    class User {
    public:
        explicit User(const QString& username);

        [[nodiscard]] const QString& getUsername() const noexcept;

    private:
        QString username;
    };
}