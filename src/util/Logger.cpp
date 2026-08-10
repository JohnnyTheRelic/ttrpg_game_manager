#include <ttrpg/util/Logger.hpp>
#include <ttrpg/util/Time.hpp>

#include <filesystem>
#include <iostream>
#include <fstream>

namespace ttrpg::util {
    Logger::Logger() {
        std::filesystem::create_directories("logs");
        logFile.open("logs/" + ttrpg::util::currentDateTime() + ".log", std::ios::app);

        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;
        }
    }

    void Logger::chat(const std::string& message) {
        std::string logMessage = "[" + ttrpg::util::currentTime() + "] [CHAT] " + message;

        std::cout << logMessage << std::endl;
        logFile << logMessage << std::endl;
    }

    void Logger::info(const std::string& message) {
        std::string logMessage = "[" + ttrpg::util::currentTime() + "] [INFO] " + message;

        std::cout << logMessage << std::endl;
        logFile << logMessage << std::endl;
    }

    void Logger::warn(const std::string& message) {
        std::string logMessage = "[" + ttrpg::util::currentTime() + "] [WARN] " + message;

        std::cout << logMessage << std::endl;
        logFile << logMessage << std::endl;
    }

    void Logger::error(const std::string& message) {
        std::string logMessage = "[" + ttrpg::util::currentTime() + "] [ERROR] " + message;

        std::cerr << logMessage << std::endl;
        logFile << logMessage << std::endl;
    }

    void Logger::debug(const std::string& message) {
        std::string logMessage = "[" + ttrpg::util::currentTime() + "] [DEBUG] " + message;

        std::cout << logMessage << std::endl;
        logFile << logMessage << std::endl;
    }
}