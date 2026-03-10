#include "MainPage/deletePage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include <string>

DeletePage::DeletePage(){
    this->pageKey="deletePage";
    this->pageName="Pagina Stergere Forma";
    this->text="\tStergere Forma\n"
                 "--Scrie b si apasa enter pentru a merge inapoi--\n";
}

void DeletePage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
}

void DeletePage::Load(){
    initNeighbourPages();
    std::string line;
     std::cout << this->text << std::flush;
    ShapeManager* sm = PageManager::getSM();
    
    if(!sm || sm->getCount() == 0){
        std::cout << "ShapeManager gol. Nu exista shape-uri de sters.\n";
    }else{
        std::cout << *sm << "\n";
        std::cout << "Introduceti ID-ul formei de sters: ";
        std::getline(std::cin, line);
        
        if(line.length() == 1 && tolower(line[0]) == 'b'){
            try{
                PageManager::changePage(this->previous);
            }catch(const std::exception& e){
                std::cerr << this->getName() + " couldn't load the page "+ line + " : "+ e.what() << '\n';
            }
        }else{
            try{
                unsigned int id = std::stoi(line);
                *sm -= id;  // stergem forma cu ID-ul dat
                std::cout << "Forma stearsa cu succes!\n";
            }catch(const std::exception& e){
                std::cerr << "Eroare la stergere: " << e.what() << '\n';
            }
        }
    }
    
    std::cout << "--Apasa enter--\n";
    std::getline(std::cin, line);
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the page: "+ e.what() << '\n';
    }
}