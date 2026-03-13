#include "MainPage/mainPage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"

MainPage::MainPage()
{
    this->pageKey = "mainPage";
    this->pageName = "Pagina Principala";
    this->text = "\tMeniu Principal\n"
                 "1. Adauga forma\n"
                 "2. Sterge forma\n"
                 "3. Modifica forma\n"
                 "4. Afiseaza forme\n"
                 "5. Iesire\n"
                 "--Scrie numarul optiunii si apasa enter--\n";
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
            std::cout << "Iesire...\n";
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