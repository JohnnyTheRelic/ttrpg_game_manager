#pragma once

#include <string>
#include <fstream>

namespace ttrpg::util {
    class Logger {
    public:
        Logger();
        void chat(const std::string& message);
        void info(const std::string& message);
        void warn(const std::string& message);
        void error(const std::string& message);
        void debug(const std::string& message);
    private:
        std::ofstream logFile;
    };
}