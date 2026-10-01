#include <ttrpg/network/Message.hpp>

#include "ttrpg.ph.h"

#include <stdexcept>

namespace ttrpg::network {
    Message::Message(MessageType type, const std::string& content) : type(type), content(content) {}

    MessageType Message::getType() const {
        return type;
    }

    const std::string& Message::getContent() const {
        return content;
    }

    std::string Message::serialize() const {
        ttrpg::network::Message message;

        message.set_type(static_cast<MessageType>(static_cast<int>(type));

        message.set_content(content);

        std::string data;

        if(!message.SerializeToString(&data)) {
            throw std::runtime_error("Failed to serialize message");
        }

        return data;
    }

    Message Message::deserialize(const std::string& data) {
        ttrpg::network::Message message;

        if(!message.ParseFromString(data)) {
            throw std::invalid_argument("Invalid protobuf message");
        }

        return Message(static_cast<MessageType>(message.type()), message.getContent());
    }
}