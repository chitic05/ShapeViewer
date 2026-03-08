#include "MainPage/mainPage.h"
#include "Page/pageManager.h"
#include "terminal.hpp"

MainPage::MainPage(){
    this->pageKey="mainPage";
    this->pageName="Pagina Principala";
    this->text="\tMeniu Principal\n"
                 "1. Adauga forma\n"
                 "2. Sterge forma\n"
                 "3. Modifica forma\n"
                 "4. Afiseaza forme\n"
                 "--Scrie numarul optiunii si apasa enter--\n";
}

void MainPage::initNeighbourPages(){
    this->previous = nullptr;
    this->next = {PageManager::getPage("addPage"), PageManager::getPage("deletePage"), PageManager::getPage("modifyPage"), PageManager::getPage("printPage")};
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