#include "ttrpg/util/String.hpp"

namespace ttrpg::util {
    std::string toUtf8(const QString& text) {
        const QByteArray encoded = text.toUtf8();

        return std::string(encoded.constData(), static_cast<std::size_t>(encoded.size()));
    }

    QString fromUtf8(const std::string& text) {
        return QString::fromUtf8(text.data(), static_cast<qsizetype>(text.size()));
    }
}
