#pragma once

#include <string>
#include <vector>

class Logger
{
public:
    static Logger &getInstance();

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger &&) = delete;

    void log(const std::string &message);
    const std::vector<std::string> &getEntries() const;
    void clear();

private:
    Logger() = default;

    std::vector<std::string> entries;
};
