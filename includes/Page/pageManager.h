#pragma once
#include "Page/page.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class ShapeManager;

class PageManager
{
public:
    static PageManager &getInstance();

    PageManager(const PageManager &) = delete;
    PageManager &operator=(const PageManager &) = delete;
    PageManager(PageManager &&) = delete;
    PageManager &operator=(PageManager &&) = delete;

    void changePage(Page *nextPage);

    Page *getPage(const std::string &pageKey);

    void setSM(ShapeManager *sm);

    ShapeManager *&getSM();

private:
    PageManager();

    ShapeManager *shapeManager;

    std::unordered_map<std::string, std::unique_ptr<Page>> allPages;

    Page *currentPage;
};