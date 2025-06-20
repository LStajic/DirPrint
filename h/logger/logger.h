#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

enum class log_level { DEBUG, INFO, WARNING, ERROR };

class logger {
public:
    logger(const std::string& file_name, log_level level = log_level::INFO)
        : log_file(file_name), min_level(level) {}

    void log(const std::string& msg, log_level level) {
        if (level < min_level) return;

        std::string level_str = level_to_str(level);
        std::string time_str = get_timestamp();

        std::string full_msg = "[" + time_str + "] [" + level_str + "] " + msg;
        std::cout << full_msg << std::endl;
        if (log_file.is_open()) {
            log_file << full_msg << std::endl;
        }
    }

    void set_log_level(log_level level) {
        min_level = level;
    }

private:
    std::ofstream log_file;
    log_level min_level;

    std::string level_to_str(log_level level) {
        switch (level) {
            case log_level::DEBUG: return "DEBUG";
            case log_level::INFO: return "INFO";
            case log_level::WARNING: return "WARNING";
            case log_level::ERROR: return "ERROR";
        }
        return "UNKNOWN";
    }

    std::string get_timestamp() {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return buf;
    }
};
