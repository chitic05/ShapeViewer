#include "MainPage/deletePage.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <string>
#include <typeinfo>
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
        std::cout << *sm << "\n";

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

            int matchCount = 0;
            for (int i = 0; i < sm->getCount(); ++i)
            {
                bool matches = false;

                if (choice == "1")
                {
                    matches = true;
                }
                else if (choice == "2")
                {
                    matches = (typeid(*(*sm)[i]) == typeid(Rectangle));
                }
                else if (choice == "3")
                {
                    matches = (typeid(*(*sm)[i]) == typeid(Diamond));
                }
                else if (choice == "4")
                {
                    matches = (typeid(*(*sm)[i]) == typeid(Square));
                }

                if (matches)
                {
                    matchCount++;
                    std::cout << *(*sm)[i] << "\n";
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