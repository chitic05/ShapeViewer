#include "MainPage/mainPage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"
MainPage::MainPage(){
    this->pageKey="mainPage";
    this->pageName="Main Page";
    this->text="\tMain page\n"
                 "1. Real numbers calculus\n"
                 "2. Matrix calculus\n"
                 "3. 2D Vector calculus\n"
                 "4. 3D Vector calculus\n"
                 "5. Complex numbers calculus\n"
                 "--Write the number that represents your pick and press enter--\n";
}

void MainPage::initNeighbourPages(){
    this->previous = nullptr;
    this->next = {PageManager::getPage("realNumPage"), PageManager::getPage("matrixPage"), PageManager::getPage("vector2DPage"), PageManager::getPage("vector3DPage"), PageManager::getPage("ComplexPage")};
}

void MainPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    
    if(onlyDigits(line)){
        try{
            PageManager::changePage(this->next[std::stoi(line)-1]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the page "+ line + " : "+ e.what() << '\n';
        }
    }else
        keyError(line, this->pageKey);
}