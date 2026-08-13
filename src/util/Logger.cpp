#include <ttrpg/util/Logger.hpp>
#include <ttrpg/util/Time.hpp>

#include <filesystem>
#include <iostream>
#include <fstream>

namespace ttrpg::util {
    Logger::Logger(LogCallback onLog) : onLog(std::move(onLog)) {
        std::filesystem::create_directories("logs");
        logFile.open("logs/" + ttrpg::util::currentDateTime() + ".log", std::ios::app);

        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;
        }
    }

    void Logger::chat(const std::string& message) {
        write("[" + ttrpg::util::currentTime() + "] [CHAT] " + message);
    }

    void Logger::info(const std::string& message) {
        write("[" + ttrpg::util::currentTime() + "] [INFO] " + message);
    }

    void Logger::warn(const std::string& message) {
        write("[" + ttrpg::util::currentTime() + "] [WARN] " + message);
    }

    void Logger::error(const std::string& message) {
        write("[" + ttrpg::util::currentTime() + "] [ERROR] " + message);
    }

    void Logger::debug(const std::string& message) {
        write("[" + ttrpg::util::currentTime() + "] [DEBUG] " + message);
    }

    void Logger::write(const std::string& message) {
        if (onLog) {
            onLog(message);
        }

        logFile << message << std::endl;
    }
}