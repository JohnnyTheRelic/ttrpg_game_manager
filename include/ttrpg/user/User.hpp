#pragma once

#include <QString>

namespace ttrpg::user {
    class User {
    public:
        explicit User(const QString& username);

        const QString& getUsername() const;

    private:
        QString username;
    };
}