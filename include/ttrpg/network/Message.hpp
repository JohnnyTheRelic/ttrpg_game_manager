#pragma once

#include <ttrpg/network/MessageType.hpp>

#include <string>

namespace ttrpg::network {
    class Message {
    public:
        Message(MessageType type, const std::string& content);

        MessageType getType() const;
        const std::string& getContent() const;

        std::string serialize() const;

        static Message deserialize(const std::string& data);
    private:
        MessageType type;
        std::string content;
    };
}