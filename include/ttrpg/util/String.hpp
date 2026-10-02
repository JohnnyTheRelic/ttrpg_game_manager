#pragma once

#include <QString>
#include <string>

namespace ttrpg::util {
    [[nodiscard]] std::string toUtf8(const QString& text);
    [[nodiscard]] QString fromUtf8(const std::string& text);
}
