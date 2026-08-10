#include <ttrpg/network/Message.hpp>

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
        return std::to_string(static_cast<int>(type)) + ":" + content;
    }

    Message Message::deserialize(const std::string& data) {
        auto pos = data.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid message format");
        }

        MessageType type = static_cast<MessageType>(std::stoi(data.substr(0, pos)));
        std::string content = data.substr(pos + 1);

        return Message(type, content);
    }
}