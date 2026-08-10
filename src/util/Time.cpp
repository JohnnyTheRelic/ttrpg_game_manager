#include <ttrpg/util/Time.hpp>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace ttrpg::util {
    std::string currentTime() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::tm local_time = *std::localtime(&time);

        std::ostringstream oss;
        oss << std::put_time(&local_time, "%H:%M:%S");
        return oss.str();
    }

    std::string currentDateTime() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::tm local_time = *std::localtime(&time);

        std::ostringstream oss;
        oss << std::put_time(&local_time, "%Y-%m-%d-%H-%M");
        return oss.str();
    }
}