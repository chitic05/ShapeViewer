#include "MainPage/deletePage.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <string>

DeletePage::DeletePage()
{
    this->pageKey = "deletePage";
    this->pageName = "Delete Shape Page";
    this->text = "\tDelete Shape\n"
                 "--Type b and press Enter to go back--\n";
}

void DeletePage::initNeighbourPages()
{
    this->previous = PageManager::getPage("mainPage");
}

void DeletePage::Load()
{
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    ShapeManager *sm = PageManager::getSM();

    if (!sm || sm->getCount() == 0)
    {
        std::cout << "ShapeManager is empty. There are no shapes to delete.\n";
    }
    else
    {
        std::cout << *sm << "\n";
        std::cout << "Enter the ID of the shape to delete: ";
        std::getline(std::cin, line);

        if (line.length() == 1 && tolower(line[0]) == 'b')
        {
            try
            {
                PageManager::changePage(this->previous);
            }
            catch (const std::exception &e)
            {
                std::cerr << this->getName() + " couldn't load the page " + line + " : " + e.what()
                          << '\n';
            }
        }
        else
        {
            try
            {
                unsigned int id = std::stoi(line);
                *sm -= id; // stergem forma cu ID-ul dat
                std::cout << "Shape deleted successfully!\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "Delete error: " << e.what() << '\n';
            }
        }
    }

    std::cout << "--Press Enter--\n";
    std::getline(std::cin, line);
    try
    {
        PageManager::changePage(this->previous);
    }
    catch (const std::exception &e)
    {
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}