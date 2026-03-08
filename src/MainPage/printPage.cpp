#include "MainPage/printPage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"
#include "Shape/shapeManager.h"
#include <string>

PrintPage::PrintPage(){
    this->pageKey="printPage";
    this->pageName="Pagina Afisare Forme";
    this->text="\tToate Formele\n"
                 "--Apasa enter pentru a merge inapoi--\n";
}

void PrintPage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
}

void PrintPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    ShapeManager* sm = PageManager::getSM();
    
    if(!sm || sm->getCount() == 0){
        std::cout << "ShapeManager gol. Nu exista shape-uri de afisat.\n";
    }else{
        std::cout << *sm << "\n";  // afisam formele
    }
    
    std::getline(std::cin, line);
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the page: " + e.what() << '\n';
    }
}