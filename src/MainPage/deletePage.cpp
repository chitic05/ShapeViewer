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
        // std::cout << *sm << "\n";

        std::cout << "\n--- Filter Options ---\n";
        std::cout << "1. Delete from all shapes\n";
        std::cout << "2. Delete Rectangle only\n";
        std::cout << "3. Delete Diamond only\n";
        std::cout << "4. Delete Square only\n";
        std::cout << "0. Go back\n";
        std::cout << "Enter your choice: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "0" || choice == "")
        {
            PageManager::changePage(this->previous);
            return;
        }

        // Clear terminal for cleaner display
    clearTerminal();
        // Display filtered shapes and ask for ID
        if (choice == "1" || choice == "2" || choice == "3" || choice == "4")
        {
            std::cout << "\n========== Filtered Shapes ==========\n";
            std::cout << "    ID | Name      | Color      | Vertices | Coordinates\n";
            std::cout << "----------------------------------------\n";

            if (choice == "1")
            {
                // Display all shapes
                for (int i = 0; i < sm->getCount(); ++i)
                {
                    std::cout << *(*sm)[i] << "\n";
                }
            }
            else if (choice == "2")
            {
                // Display only Rectangles using dynamic_cast
                sm->printAllRectangles();
            }
            else if (choice == "3")
            {
                // Display only Diamonds using dynamic_cast
                sm->printAllDiamonds();
            }
            else if (choice == "4")
            {
                // Display only Squares using dynamic_cast
                sm->printAllSquares();
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
                *sm -= id; // stergem forma cu ID-ul dat
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