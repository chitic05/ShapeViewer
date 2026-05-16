#include "MainPage/addPage.h"
#include "Factory/abstractFactory.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <memory>

AddPage::AddPage() : Page(), factory(nullptr)
{
    this->pageKey = "addPage";
    this->pageName = "Add Shape Page";
    this->text = "\tAdd Shape\n"
                 "--Type b and press Enter to go back--\n"
                 "--Press Enter to continue--\n";
}

void AddPage::initNeighbourPages()
{
    this->previous = PageManager::getInstance().getPage("mainPage");
}

void AddPage::setFactory(IShapeFactory *shapeFactory)
{
    factory = shapeFactory;
}

void AddPage::Load()
{
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    // std::getline(std::cin, line);

    if (line.length() == 1 && tolower(line[0]) == 'b')
    {
        try
        {
            PageManager::getInstance().changePage(this->previous);
        }
        catch (const std::exception &e)
        {
            std::cerr << this->getName() + " couldn't load the page " + line + " : " + e.what()
                      << '\n';
        }
    }
    else
    {
        ShapeManager *sm = PageManager::getInstance().getSM();
        if (!sm)
        {
            std::cerr << "ShapeManager is not initialized!\n";
            std::cout << "--Press Enter--\n";
            std::getline(std::cin, line);
            PageManager::getInstance().changePage(this->previous);
            return;
        }

        std::cout << "\n--- Select Shape Family ---\n";
        std::cout << "1. Perpendicular (Rectangle / Right Triangle)\n";
        std::cout << "2. Equal (Square / Equilateral Triangle)\n";
        std::cout << "3. Romb (Diamond / Equilateral Triangle)\n";
        std::cout << "0. Cancel\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, line);

        if (line == "0" || line == "")
        {
            PageManager::getInstance().changePage(this->previous);
            return;
        }

        if (line == "1")
            PageManager::getInstance().setShapeFactory(std::make_unique<PerpendicularFactory>());
        else if (line == "2")
            PageManager::getInstance().setShapeFactory(std::make_unique<EqualFactory>());
        else if (line == "3")
            PageManager::getInstance().setShapeFactory(std::make_unique<RombFactory>());
        else
        {
            std::cerr << "Invalid choice!\n";
            PageManager::getInstance().changePage(this->previous);
            return;
        }

        if (!factory)
        {
            std::cerr << "ShapeFactory is not initialized!\n";
            std::cout << "--Press Enter--\n";
            std::getline(std::cin, line);
            PageManager::getInstance().changePage(this->previous);
            return;
        }

        std::cout << "\n--- Select Shape Type ---\n";
        std::cout << "1. Quadrilateral\n";
        std::cout << "2. Triangle\n";
        std::cout << "0. Cancel\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, line);

        if (line == "0" || line == "")
        {
            PageManager::getInstance().changePage(this->previous);
            return;
        }

        Shape *newShape = nullptr;

        try
        {
            if (line == "1")
            {
                newShape = factory->createPatrulater();
                std::cout << "Quadrilateral added successfully!\n";
            }
            else if (line == "2")
            {
                newShape = factory->createTriangle();
                std::cout << "Triangle added successfully!\n";
            }
            else
            {
                std::cerr << "Invalid choice!\n";
                PageManager::getInstance().changePage(this->previous);
                return;
            }

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
        PageManager::getInstance().changePage(this->previous);
    }
    catch (const std::exception &e)
    {
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}