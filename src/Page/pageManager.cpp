#include "Page/pageManager.h"
#include "MainPage/addPage.h"
#include "MainPage/deletePage.h"
#include "MainPage/mainPage.h"
#include "MainPage/modifyPage.h"
#include "MainPage/printPage.h"
#include "Shape/shapeManager.h"
#include "terminal.hpp"
#include <stdexcept>

ShapeManager *PageManager::shapeManager = nullptr;
Page *PageManager::currentPage = nullptr;

std::unordered_map<std::string, std::unique_ptr<Page>> PageManager::allPages = []()
{
    std::unordered_map<std::string, std::unique_ptr<Page>> pages;
    pages["mainPage"] = std::make_unique<MainPage>();
    pages["addPage"] = std::make_unique<AddPage>();
    pages["deletePage"] = std::make_unique<DeletePage>();
    pages["printPage"] = std::make_unique<PrintPage>();
    pages["modifyPage"] = std::make_unique<ModifyPage>();
    return pages;
}();

void PageManager::setSM(ShapeManager *sm)
{
    PageManager::shapeManager = sm;
}

ShapeManager *&PageManager::getSM()
{
    return PageManager::shapeManager;
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
