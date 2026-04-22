#include "MainPage/addPage.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"

AddPage::AddPage() : Page()
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
        // Shape type selection menu
        std::cout << "\n--- Select Shape Type ---\n";
        std::cout << "1. Rectangle\n";
        std::cout << "2. Diamond\n";
        std::cout << "3. Square\n";
        std::cout << "0. Cancel\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, line);

        if (line == "0" || line == "")
        {
            PageManager::changePage(this->previous);
            return;
        }

        ShapeManager *sm = PageManager::getSM();
        if (!sm)
        {
            std::cerr << "ShapeManager is not initialized!\n";
            std::cout << "--Press Enter--\n";
            std::getline(std::cin, line);
            PageManager::changePage(this->previous);
            return;
        }

        Shape *newShape = nullptr;

        try
        {
            if (line == "1")
            {
                // Rectangle - use static create()
                newShape = Rectangle::create();
                std::cout << "Rectangle added successfully!\n";
            }
            else if (line == "2")
            {
                // Diamond - use static create()
                newShape = Diamond::create();
                std::cout << "Diamond added successfully!\n";
            }
            else if (line == "3")
            {
                // Square - use static create()
                newShape = Square::create();
                std::cout << "Square added successfully!\n";
            }
            else
            {
                std::cerr << "Invalid choice!\n";
                PageManager::changePage(this->previous);
                return;
            }

            // Add the created shape to ShapeManager (takes ownership of pointer)
            if (newShape)
            {
                *sm += newShape;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error creating shape: " << e.what() << "\n";
        }
    }

    std::cout << "--Press Enter--\n";
    try
    {
        std::string dummy;
        std::getline(std::cin, dummy);
        PageManager::changePage(this->previous);
    }
    catch (const std::exception &e)
    {
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}