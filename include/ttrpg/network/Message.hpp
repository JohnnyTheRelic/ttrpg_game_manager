#pragma once

#include <ttrpg/network/MessageType.hpp>

#include <QString>
#include <string>

namespace ttrpg::network {
    class Message {
    public:
        explicit Message();

        Message(MessageType type, const QString& content);

        MessageType getType() const;
        const QString& getContent() const;

        std::string serialize() const;

        static Message deserialize(const std::string& data);
    private:
        MessageType type;
        QString content;
    };
}