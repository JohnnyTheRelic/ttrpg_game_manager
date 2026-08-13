#pragma once

#include <string>
#include <fstream>
#include <functional>

namespace ttrpg::util {
    class Logger {
    public:
        using LogCallback = std::function<void(const std::string&)>;

        explicit Logger(LogCallback onLog);

        void chat(const std::string& message);
        void info(const std::string& message);
        void warn(const std::string& message);
        void error(const std::string& message);
        void debug(const std::string& message);
    private:
        std::ofstream logFile;
        LogCallback onLog;
        
        void write(const std::string& message);
    };
}