#include <iostream>
#include "Page/pageManager.h"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include "Math/matrix.h"
#include "Page/pageManager.h"

int main(){
    ShapeManager* sm = new ShapeManager("My Shapes");
    PageManager::setSM(*sm);
    
    PageManager::changePage(PageManager::getPage("mainPage"));
    
    delete sm;
    return 0;
}