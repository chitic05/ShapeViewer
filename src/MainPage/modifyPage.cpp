#include "MainPage/modifyPage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"
#include "Shape/shape.h"
#include "Shape/shapeManager.h"
#include "Math/matrix.h"
#include <string>

ModifyPage::ModifyPage(){
    this->pageKey="modifyPage";
    this->pageName="Pagina Modificare Forma";
    this->text="\tModificare Forma\n"
                 "--Scrie b si apasa enter pentru a merge inapoi--\n";
}

void ModifyPage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
}

void ModifyPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    ShapeManager* sm = PageManager::getSM();
    
    if(!sm || sm->getCount() == 0){
        std::cout << "ShapeManager gol. Nu exista shape-uri de modificat.\n";
        std::cout << "--Apasa enter--\n";
        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }
    
    std::cout << *sm << "\n";
    std::cout << "Introduceti ID-ul shape-ului de modificat: ";
    std::getline(std::cin, line);
    
    if(line.length() == 1 && tolower(line[0]) == 'b'){
        PageManager::changePage(this->previous);
        return;
    }
    
    if(!onlyDigits(line)){
        std::cerr << "ID invalid!\n";
        std::cout << "--Apasa enter--\n";

        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }
    
    unsigned int shapeId = std::stoi(line);
    
    int shapeIndex = -1;
    for(unsigned int i = 0; i < sm->getCount(); ++i){
        if((*sm)[i].getId() == shapeId){
            shapeIndex = i;
            break;
        }
    }
    
    if(shapeIndex == -1){
        std::cerr << "Forma cu ID-ul " << shapeId << " nu a fost gasita!\n";
        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }
    
    std::cout << "\nAlegeti tipul de transformare:\n";
    std::cout << "1. Scalare\n";
    std::cout << "2. Rotatie\n";
    std::cout << "3. Translatie\n";
    std::cout << "Optiune: ";
    std::getline(std::cin, line);
    
    if(line.length() == 1 && tolower(line[0]) == 'b'){
        PageManager::changePage(this->previous);
        return;
    }
    
    if(!onlyDigits(line)){
        std::cerr << "Optiune invalida!\n";
        std::cout << "--Apasa enter--\n";
        std::getline(std::cin, line);
        PageManager::changePage(this->previous);
        return;
    }
    
    int option = std::stoi(line);
    Matrix transformMatrix(3);
    
    if(option == 1){
        std::cout << "Introduceti factorul de scalare (ex: 2.0 pentru dublu, 0.5 pentru jumatate): ";
        std::getline(std::cin, line);
        try{
            float scale = std::stof(line);
            transformMatrix = Matrix::genScaleMatrix(scale);
            (*sm)[shapeIndex] = transformMatrix * (*sm)[shapeIndex];
            std::cout << "Forma scalata cu succes!\n";
        }catch(...){
            std::cerr << "Factor de scalare invalid!\n";
        }
    }else if(option == 2){
        std::cout << "Introduceti unghiul de rotatie in grade (ex: 90, 45, -30): ";
        std::getline(std::cin, line);
        try{
            float angle = std::stof(line);
            transformMatrix = Matrix::genRotateMatrix(angle);
            (*sm)[shapeIndex] = transformMatrix * (*sm)[shapeIndex];
            std::cout << "Forma rotita cu succes!\n";
        }catch(...){
            std::cerr << "Unghi invalid!\n";
        }
    }else if(option == 3){
        std::cout << "Introduceti deplasarea pe axa X (ex: 50, -30): ";
        std::getline(std::cin, line);
        try{
            float dx = std::stof(line);
            std::cout << "Introduceti deplasarea pe axa Y (ex: 50, -30): ";
            std::getline(std::cin, line);
            float dy = std::stof(line);
            transformMatrix = Matrix::genTranslateMatrix(dx, dy);
            (*sm)[shapeIndex] = transformMatrix * (*sm)[shapeIndex];
            std::cout << "Forma translatata cu succes!\n";
        }catch(...){
            std::cerr << "Valori de deplasare invalide!\n";
        }
    }else{
        std::cerr << "Optiune invalida!\n";
    }
    
    std::cout << "\nForme dupa modificare:\n";
    std::cout << *sm << "\n";
    std::cout << "--Apasa enter--\n";
    std::getline(std::cin, line);
    PageManager::changePage(this->previous);
}
