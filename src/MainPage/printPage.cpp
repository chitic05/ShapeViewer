#include "MainPage/printPage.h"
#include "Math/point.h"
#include "Page/pageManager.h"
#include "SDL3/SDL.h"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

PrintPage::PrintPage()
{
    this->pageKey = "printPage";
    this->pageName = "Display Shapes Page";
    this->text = "\tAll Shapes\n"
                 "--Press Enter to go back--\n";
}

void PrintPage::initNeighbourPages()
{
    this->previous = PageManager::getPage("mainPage");
}

void PrintPage::Load()
{
    initNeighbourPages();
    std::cout << this->text << std::flush;
    ShapeManager *sm = PageManager::getSM();

    if (!sm || sm->getCount() == 0)
    {
        std::cout << "ShapeManager is empty. There are no shapes to display.\n";
        std::cout << "--Press Enter--\n";
        std::string line;
        std::getline(std::cin, line);
    }
    else
    {
        std::cout << *sm << "\n";

        std::cout << "\nEnter the ID of the shape you want to view: ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "")
        {
            PageManager::changePage(this->previous);
            return;
        }
        int selectedId = -1;
        try
        {
            selectedId = std::stoi(line);
        }
        catch (...)
        {
            std::cout << "Invalid ID!\n";
            std::cout << "--Press Enter--\n";
            std::getline(std::cin, line);
            PageManager::changePage(this->previous);
            return;
        }

        // Luam forma cu id-ul respsectiv
        Shape *selectedShape = nullptr;
        for (int i = 0; i < sm->getCount(); ++i)
        {
            if ((*sm)[i].getId() == selectedId)
            {
                selectedShape = &(*sm)[i];
                break;
            }
        }

        if (!selectedShape)
        {
            std::cout << "Shape with ID " << selectedId << " was not found!\n";
            std::cout << "--Press Enter--\n";
            std::getline(std::cin, line);
            PageManager::changePage(this->previous);
            return;
        }

        std::cout << "\nDrawing shape: " << *selectedShape << "\n" << std::flush;
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
            std::cout << "--Press Enter--\n";
            std::string line;
            std::getline(std::cin, line);
            PageManager::changePage(this->previous);
            return;
        }

        SDL_Window *window = SDL_CreateWindow("Shapes Viewer", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (!window)
        {
            std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
            SDL_Quit();
            std::cout << "--Press Enter--\n";
            std::string line;
            std::getline(std::cin, line);
            PageManager::changePage(this->previous);
            return;
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
        if (!renderer)
        {
            std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            std::cout << "--Press Enter--\n";
            std::string line;
            std::getline(std::cin, line);
            PageManager::changePage(this->previous);
            return;
        }

        std::cout << "SDL window opened. Press 'b' to close and return.\n"
                  << std::flush;

        bool running = true;
        SDL_Event event;

        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_EVENT_KEY_DOWN)
                {
                    if (event.key.key == SDLK_B)
                    {
                        running = false;
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            switch (selectedShape->getColor())
            {
            case Color::RED:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            case Color::BLUE:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
            case Color::GREEN:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                break;
            }

            for (int j = 0; j < selectedShape->getCount(); ++j)
            {
                Point &p1 = (*selectedShape)[j];
                Point &p2 = (*selectedShape)[(j + 1) % selectedShape->getCount()];
                SDL_RenderLine(renderer, p1[0] + 400, -p1[1] + 300, p2[0] + 400, -p2[1] + 300);
                //- deoarece sistemul de coordonate SDL e diferti
            }

            SDL_RenderPresent(renderer);

            SDL_Delay(16);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        std::cout << "Window closed.\n" << std::flush;
    }

    try
    {
        PageManager::changePage(this->previous);
    }
    catch (const std::exception &e)
    {
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}