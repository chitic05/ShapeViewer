#include "MainPage/mainPage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"

MainPage::MainPage()
{
    this->pageKey = "mainPage";
    this->pageName = "Main Page";
    this->text = "\tMain Menu\n"
                 "1. Add shape\n"
                 "2. Delete shape\n"
                 "3. Modify shape\n"
                 "4. Display shapes\n"
                 "5. Exit\n"
                 "--Type the option number and press Enter--\n";
}

void MainPage::initNeighbourPages()
{
    this->previous = nullptr;
    this->next = {PageManager::getPage("addPage"), PageManager::getPage("deletePage"),
                  PageManager::getPage("modifyPage"), PageManager::getPage("printPage")};
}

void MainPage::Load()
{
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    // std::cout << next.size();
    if (onlyDigits(line))
    {
        int option = std::stoi(line);
        if (option == 5)
        {
            std::cout << "Exiting...\n";
            return;
        }
        if (option <= this->next.size() && option > 0)
        {
            try
            {
                PageManager::changePage(this->next[option - 1]);
            }
            catch (const std::exception &e)
            {
                std::cerr << this->getName() + " couldn't load the page " + line + " : " + e.what()
                          << '\n';
            }
        }
        else
        {
            keyError(line, this->pageKey);
        }
    }
    else
        keyError(line, this->pageKey);
}