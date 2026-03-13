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
    static void changePage(Page *nextPage);

    static Page *getPage(const std::string &pageKey);

    static void setSM(ShapeManager *sm);

    static ShapeManager *&getSM();

private:
    static ShapeManager *shapeManager;

    static std::unordered_map<std::string, std::unique_ptr<Page>> allPages;

    static Page *currentPage;
};