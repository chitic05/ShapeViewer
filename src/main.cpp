#include "Page/pageManager.h"
#include "Shape/shapeManager.h"
#include <iostream>

int main()
{
    ShapeManager *sm = new ShapeManager("My Shapes");
    PageManager::setSM(sm);

    PageManager::changePage(PageManager::getPage("mainPage"));

    delete sm;
    return 0;
}