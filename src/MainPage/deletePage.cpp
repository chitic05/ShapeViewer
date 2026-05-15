#include "MainPage/deletePage.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <string>
#include <cstdlib>
#include <algorithm>

DeletePage::DeletePage() : Page()
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
        std::cout << "\n--- Filter Options ---\n";
        std::cout << "1. Delete from all shapes\n";
        std::cout << "2. Delete Rectangle only\n";
        std::cout << "3. Delete Diamond only\n";
        std::cout << "4. Delete Square only\n";
        std::cout << "5. Delete shapes by color\n";
        std::cout << "6. Delete shapes sorted by perimeter\n";
        std::cout << "7. Find shape by ID\n";
        std::cout << "0. Go back\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "0" || choice == "")
        {
            PageManager::changePage(this->previous);
            return;
        }

        clearTerminal();

        if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
        {
            std::cout << "\n========== Filtered Shapes ==========\n";
            std::cout << "    ID | Name      | Color      | Vertices | Coordinates\n";
            std::cout << "----------------------------------------\n";

            auto& allShapes = sm->getRepository().getAllShapes();
            int matchCount = 0;

            if (choice == "1")
            {
                for (const auto& shape : allShapes) {
                    matchCount++;
                    std::cout << *shape << "\n";
                }
            }
            else if (choice == "2" || choice == "3" || choice == "4")
            {
                for (const auto& shape : allShapes)
                {
                    bool matches = false;
                    if (choice == "2")
                        matches = (dynamic_cast<Rectangle*>(shape) != nullptr);
                    else if (choice == "3")
                        matches = (dynamic_cast<Diamond*>(shape) != nullptr);
                    else if (choice == "4")
                        matches = (dynamic_cast<Square*>(shape) != nullptr);

                    if (matches)
                    {
                        matchCount++;
                        std::cout << *shape << "\n";
                    }
                }
            }
            else if (choice == "5")
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
            else if (choice == "6")
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
            else if (choice == "7")
            {
                std::cout << "Enter shape ID: ";
                std::string idStr;
                std::getline(std::cin, idStr);
                
                try {
                    unsigned int id = std::stoi(idStr);
                    auto shape = sm->getRepository().findShapeById(id);
                    matchCount++;
                    std::cout << *shape << "\n";
                } catch (...) {
                    std::cout << "Invalid ID or shape not found\n";
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
                *sm -= id;
                std::cout << "Shape deleted successfully!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Delete error: ID is invalid!\n";
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