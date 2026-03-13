#pragma once

#include "Page/pageManager.h"
#include <cstdlib>
#include <iostream>
#include <string>

inline void clearTerminal()
{
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H" << std::flush;
#endif
}

inline void keyError(std::string &line, std::string &pageKey)
{
    std::cout << "Error: Key \"" << line << "\" doesn't do anything" << std::endl;
    std::string b;

    std::getline(std::cin, b);

    try
    {
        PageManager::changePage(PageManager::getPage(pageKey));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to reload page: " << e.what() << std::endl;
    }
}

inline void NaNError(std::string &line, std::string &pageKey)
{
    std::cout << "Error: \"" << line << "\" isn't a number" << std::endl;
    std::string b;

    std::getline(std::cin, b);

    try
    {
        PageManager::changePage(PageManager::getPage(pageKey));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to reload page: " << e.what() << std::endl;
    }
}

inline bool onlyDigits(const std::string &str)
{
    if (str.empty())
        return false;

    for (char ch : str)
    {
        if (ch < '0' || ch > '9')
        {
            return false;
        }
    }
    return true;
}