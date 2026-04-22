#include "MainPage/modifyPage.h"
#include "Math/matrix.h"
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <string>
#include <typeinfo>

ModifyPage::ModifyPage() : Page()
{
    this->pageKey = "modifyPage";
    this->pageName = "Modify Shape Page";
    this->text = "\tModify Shape\n"
                 "--Type b and press Enter to go back--\n";
}

void ModifyPage::initNeighbourPages()
{
    this->previous = PageManager::getPage("mainPage");
}

void ModifyPage::Load()
{
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    ShapeManager *sm = PageManager::getSM();

    if (!sm || sm->getCount() == 0)
    {
        std::cout << "ShapeManager is empty. There are no shapes to modify.\n";
        std::cout << "--Press Enter--\n";
        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }

    std::cout << "\n--- Filter Options ---\n";
    std::cout << "1. Modify from all shapes\n";
    std::cout << "2. Modify Rectangle only\n";
    std::cout << "3. Modify Diamond only\n";
    std::cout << "4. Modify Square only\n";
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

    std::cout << "Enter the ID of the shape to modify: ";
    std::getline(std::cin, line);

    if (line.length() == 1 && tolower(line[0]) == 'b')
    {
        PageManager::changePage(this->previous);
        return;
    }

    if (!onlyDigits(line))
    {
        std::cerr << "Invalid ID!\n";
        std::cout << "--Press Enter--\n";

        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }

    unsigned int shapeId = std::stoi(line);

    int shapeIndex = -1;
    for (unsigned int i = 0; i < sm->getCount(); ++i)
    {
        if ((*sm)[i]->getId() == shapeId)
        {
            shapeIndex = i;
            break;
        }
    }

    if (shapeIndex == -1)
    {
        std::cerr << "Shape with ID " << shapeId << " was not found!\n";
        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }

    std::cout << "\nChoose transformation type:\n";
    std::cout << "1. Scale\n";
    std::cout << "2. Rotate\n";
    std::cout << "3. Translate\n";
    std::cout << "Option: ";
    std::getline(std::cin, line);

    if (line.length() == 1 && tolower(line[0]) == 'b')
    {
        PageManager::changePage(this->previous);
        return;
    }

    if (!onlyDigits(line))
    {
        std::cerr << "Invalid option!\n";
        std::cout << "--Press Enter--\n";
        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }

    int option = std::stoi(line);
    Matrix transformMatrix(3);

    if (option == 1)
    {
        std::cout
            << "Enter scaling factor (e.g. 2.0 for double size, 0.5 for half size): ";
        std::getline(std::cin, line);
        try
        {
            float scale = std::stof(line);
            transformMatrix = Matrix::genScaleMatrix(scale);
            *(*sm)[shapeIndex] = transformMatrix * *(*sm)[shapeIndex];
            std::cout << "Shape scaled successfully!\n";
        }
        catch (...)
        {
            std::cerr << "Invalid scaling factor!\n";
        }
    }
    else if (option == 2)
    {
        std::cout << "Enter rotation angle in degrees (e.g. 90, 45, -30): ";
        std::getline(std::cin, line);
        try
        {
            float angle = std::stof(line);
            transformMatrix = Matrix::genRotateMatrix(-angle);
            *(*sm)[shapeIndex] = transformMatrix * *(*sm)[shapeIndex];
            std::cout << "Shape rotated successfully!\n";
        }
        catch (...)
        {
            std::cerr << "Invalid angle!\n";
        }
    }
    else if (option == 3)
    {
        std::cout << "Enter translation on X axis (e.g. 50, -30): ";
        std::getline(std::cin, line);
        try
        {
            float dx = std::stof(line);
            std::cout << "Enter translation on Y axis (e.g. 50, -30): ";
            std::getline(std::cin, line);
            float dy = std::stof(line);
            transformMatrix = Matrix::genTranslateMatrix(dx, dy);
            *(*sm)[shapeIndex] = transformMatrix * *(*sm)[shapeIndex];
            std::cout << "Shape translated successfully!\n";
        }
        catch (...)
        {
            std::cerr << "Invalid translation values!\n";
        }
    }
    else
    {
        std::cerr << "Invalid option!\n";
    }

    std::cout << "\nShapes after modification:\n";
    std::cout << *sm << "\n";
    std::cout << "--Press Enter--\n";
    std::getline(std::cin, line);
    PageManager::changePage(this->previous);
}
