#include "Utility/logger.h"

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string &message)
{
    entries.push_back(message);
}

const std::vector<std::string> &Logger::getEntries() const
{
    return entries;
}

void Logger::clear()
{
    entries.clear();
}
