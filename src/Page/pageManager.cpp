#include "Page/pageManager.h"
#include "MainPage/addPage.h"
#include "MainPage/deletePage.h"
#include "MainPage/mainPage.h"
#include "MainPage/modifyPage.h"
#include "MainPage/printPage.h"
#include "Shape/shapeManager.h"
// Adaugă header-ul fabricii tale abstracte aici dacă nu e inclus în altă parte
// #include "Shape/shapeFactory.h" 
#include "terminal.hpp"
#include <stdexcept>

// Constructorul - inițializează pointerii pe nullptr și încarcă paginile în map
PageManager::PageManager()
    : shapeManager(nullptr), shapeFactory(nullptr), currentPage(nullptr)
{
    allPages["mainPage"] = std::make_unique<MainPage>();
    allPages["addPage"] = std::make_unique<AddPage>();
    allPages["deletePage"] = std::make_unique<DeletePage>();
    allPages["printPage"] = std::make_unique<PrintPage>();
    allPages["modifyPage"] = std::make_unique<ModifyPage>();
}

// Meyers Singleton - instanța unică statică locală
PageManager &PageManager::getInstance()
{
    static PageManager instance;
    return instance;
}

void PageManager::setSM(ShapeManager *sm)
{
    shapeManager = sm;
}

ShapeManager *&PageManager::getSM()
{
    return shapeManager;
}

void PageManager::setShapeFactory(std::unique_ptr<IShapeFactory> factory)
{
    shapeFactory = std::move(factory); 
    auto addPage = dynamic_cast<AddPage*>(getPage("addPage"));
    if(addPage){
        addPage->setFactory(shapeFactory.get());
    }
}

void PageManager::changePage(Page *nextPage)
{
    clearTerminal();
    currentPage = nextPage;
    if (currentPage)
        currentPage->Load();
    else
        throw std::runtime_error("Page can't be loaded!");
}

Page *PageManager::getPage(const std::string &pageKey)
{
    auto it = allPages.find(pageKey);
    if (it != allPages.end())
        return it->second.get();
    return nullptr;
}