#include "MainPage/addPage.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"

AddPage::AddPage()
{
    this->pageKey = "addPage";
    this->pageName = "Add Shape Page";
    this->text = "\tAdd Shape\n"
                 "--Type b and press Enter to go back--\n"
                 "--Press Enter to continue--\n";
}

void AddPage::initNeighbourPages()
{
    this->previous = PageManager::getPage("mainPage");
}

void AddPage::Load()
{
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
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
        Shape shape;
        std::cin >> shape; // citim forma
        ShapeManager *sm = PageManager::getSM();

        if (sm)
        {
            *sm += shape;
            std::cout << "Shape added successfully!\n";
        }
        else
        {
            std::cerr << "ShapeManager is not initialized!\n";
        }
    }

    std::cout << "--Press Enter--\n";
    try
    {
        PageManager::changePage(this->previous);
    }
    catch (const std::exception &e)
    {
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}