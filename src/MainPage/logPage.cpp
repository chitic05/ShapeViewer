#include "MainPage/logPage.h"
#include "Page/pageManager.h"
#include "Utility/logger.h"
#include <iostream>

LogPage::LogPage() : Page()
{
    this->pageKey = "logPage";
    this->pageName = "Journal Page";
    this->text = "\tJournal\n--Press Enter to go back--\n";
}

void LogPage::initNeighbourPages()
{
    this->previous = PageManager::getInstance().getPage("mainPage");
}

void LogPage::Load()
{
    initNeighbourPages();
    std::cout << this->text << std::flush;

    const auto &entries = Logger::getInstance().getEntries();
    if (entries.empty())
    {
        std::cout << "(Journal is empty)\n";
    }
    else
    {
        int index = 1;
        for (const auto &line : entries)
        {
            std::cout << "[" << index++ << "] " << line << "\n";
        }
    }

    std::string line;
    std::getline(std::cin, line);
    PageManager::getInstance().changePage(this->previous);
}
