#include <ttrpg/network/Message.hpp>

#include "ttrpg.pb.h"

#include <stdexcept>

namespace ttrpg::network {
    Message::Message() : type(MessageType::ChatMessage), content("") {}

    Message::Message(MessageType type, const QString& content) : type(type), content(content) {}

    MessageType Message::getType() const {
        return type;
    }

    const QString& Message::getContent() const {
        return content;
    }

    std::string Message::serialize() const {
        ttrpg::protocol::Message proto;

        proto.set_type(static_cast<ttrpg::protocol::MessageType>(static_cast<int>(type)));

        const QByteArray utf8Content = content.toUtf8();

        proto.set_content(utf8Content.constData(), static_cast<std::size_t>(utf8Content.size()));

        std::string data;

        if(!proto.SerializeToString(&data)) {
            throw std::runtime_error("Failed to serialize message");
        }

        return data;
    }

    Message Message::deserialize(const std::string& data) {
        ttrpg::protocol::Message proto;

        if(!proto.ParseFromString(data)) {
            throw std::invalid_argument("Invalid protobuf message");
        }

        const auto type = static_cast<MessageType>(static_cast<int>(proto.type()));
        const QString message = QString::fromUtf8(proto.content().data(), static_cast<qsizetype>(proto.content().size()));

        return Message(static_cast<MessageType>(type), message);
    }
}