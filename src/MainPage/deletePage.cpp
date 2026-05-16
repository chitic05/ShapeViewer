#include "MainPage/deletePage.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include "Shape/shapes/rightTriangle.h"
#include "Shape/shapes/equilateralTriangle.h"
#include "Factory/abstractFactory.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <string>
#include <cstdlib>
#include <algorithm>
#include <functional>

DeletePage::DeletePage() : Page()
{
    this->pageKey = "deletePage";
    this->pageName = "Delete Shape Page";
    this->text = "\tDelete Shape\n"
                 "--Type b and press Enter to go back--\n";
}

void DeletePage::initNeighbourPages()
{
    this->previous = PageManager::getInstance().getPage("mainPage");
}

void DeletePage::Load()
{
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    ShapeManager *sm = PageManager::getInstance().getSM();

    if (!sm || sm->getCount() == 0)
    {
        std::cout << "ShapeManager is empty. There are no shapes to delete.\n";
    }
    else
    {
        std::cout << "\n--- Filter Options ---\n";
        std::cout << "1. Delete from all shapes\n";
        std::cout << "2. Delete quadrilaterals\n";
        std::cout << "3. Delete triangles\n";
        std::cout << "4. Delete shapes by color\n";
        std::cout << "5. Delete shapes sorted by perimeter\n";
        std::cout << "6. Delete shapes sorted by name\n";
        std::cout << "0. Go back\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "0" || choice == "")
        {
            PageManager::getInstance().changePage(this->previous);
            return;
        }

        clearTerminal();

        if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
        {
            std::cout << "\n========== Filtered Shapes ==========\n";
            std::cout << "    ID | Name      | Color      | Vertices | Coordinates\n";
            std::cout << "----------------------------------------\n";

            auto& allShapes = sm->getRepository().getAllShapes();
            int matchCount = 0;
            std::function<bool(Shape*)> filter;

            if (choice == "1")
            {
                for (const auto& shape : allShapes) {
                    matchCount++;
                    std::cout << *shape << "\n";
                }
            }
            else if (choice == "2")
            {
                std::cout << "\n--- Quadrilateral Options ---\n";
                std::cout << "1. All quadrilaterals\n";
                std::cout << "2. Rectangle only\n";
                std::cout << "3. Diamond only\n";
                std::cout << "4. Square only\n";
                std::cout << "0. Go back\n";
                std::cout << "Enter your choice: ";
                std::string subChoice;
                std::getline(std::cin, subChoice);

                if (subChoice == "0" || subChoice == "")
                {
                    PageManager::getInstance().changePage(this->previous);
                    return;
                }

                if (subChoice == "1")
                    filter = [](Shape* s) { return dynamic_cast<Patrulater*>(s) != nullptr; };
                else if (subChoice == "2")
                    filter = [](Shape* s) { return dynamic_cast<Rectangle*>(s) != nullptr; };
                else if (subChoice == "3")
                    filter = [](Shape* s) { return dynamic_cast<Diamond*>(s) != nullptr; };
                else if (subChoice == "4")
                    filter = [](Shape* s) { return dynamic_cast<Square*>(s) != nullptr; };
                else
                {
                    std::cerr << "Invalid choice!\n";
                    PageManager::getInstance().changePage(this->previous);
                    return;
                }

                for (const auto& shape : allShapes)
                {
                    if (filter(shape))
                    {
                        matchCount++;
                        std::cout << *shape << "\n";
                    }
                }
            }
            else if (choice == "3")
            {
                std::cout << "\n--- Triangle Options ---\n";
                std::cout << "1. All triangles\n";
                std::cout << "2. Right triangle only\n";
                std::cout << "3. Equilateral triangle only\n";
                std::cout << "0. Go back\n";
                std::cout << "Enter your choice: ";
                std::string subChoice;
                std::getline(std::cin, subChoice);

                if (subChoice == "0" || subChoice == "")
                {
                    PageManager::getInstance().changePage(this->previous);
                    return;
                }

                if (subChoice == "1")
                    filter = [](Shape* s) { return dynamic_cast<Triangle*>(s) != nullptr; };
                else if (subChoice == "2")
                    filter = [](Shape* s) { return dynamic_cast<RightTriangle*>(s) != nullptr; };
                else if (subChoice == "3")
                    filter = [](Shape* s) { return dynamic_cast<EquilateralTriangle*>(s) != nullptr; };
                else
                {
                    std::cerr << "Invalid choice!\n";
                    PageManager::getInstance().changePage(this->previous);
                    return;
                }

                for (const auto& shape : allShapes)
                {
                    if (filter(shape))
                    {
                        matchCount++;
                        std::cout << *shape << "\n";
                    }
                }
            }
            else if (choice == "4")
            {
                std::cout << "Enter color (RED/GREEN/BLUE): ";
                std::string colorStr;
                std::getline(std::cin, colorStr);
                
                Color filterColor = Color::RED;
                if (colorStr == "GREEN") filterColor = Color::GREEN;
                else if (colorStr == "BLUE") filterColor = Color::BLUE;
                
                auto colorShapes = sm->getRepository().findShapesByColor(filterColor);
                for (const auto& shape : colorShapes)
                {
                    matchCount++;
                    std::cout << *shape << "\n";
                }
            }
            else if (choice == "5")
            {
                auto sorted = allShapes;
                std::sort(sorted.begin(), sorted.end(),
                         [](Shape* a, Shape* b) { return a->getPerimeter() < b->getPerimeter(); });
                
                for (const auto& shape : sorted)
                {
                    matchCount++;
                    std::cout << *shape << "\n";
                }
            }
            else if (choice == "6")
            {
                auto sorted = allShapes;
                std::sort(sorted.begin(), sorted.end(),
                         [](Shape* a, Shape* b) { return a->getName() < b->getName(); });

                for (const auto& shape : sorted)
                {
                    matchCount++;
                    std::cout << *shape << "\n";
                }
            }

            if (matchCount == 0)
            {
                std::cout << "  (No shapes matching the filter)\n";
            }
            std::cout << "====================================\n";
        }

        std::cout << "Enter the ID of the shape to delete: ";
        std::getline(std::cin, line);

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
            try
            {
                unsigned int id = std::stoi(line);
                sm->getRepository().findShapeById(id);
                *sm -= id;
                std::cout << "Shape deleted successfully!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Delete error: ID is invalid or not found!\n";
            }
        }
    }

    std::cout << "--Press Enter--\n";
    std::getline(std::cin, line);
    try
    {
        PageManager::getInstance().changePage(this->previous);
    }
    catch (const std::exception &e)
    {
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}