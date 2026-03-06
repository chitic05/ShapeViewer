#include "Page/pageManager.h"
#include "terminal.hpp"
#include <stdexcept>

Page* PageManager::currentPage = nullptr;

std::unordered_map<std::string, std::unique_ptr<Page>> PageManager::allPages = [](){
    std::unordered_map<std::string, std::unique_ptr<Page>> pages;
    return pages;
}();

void PageManager::changePage(Page* nextPage){
    clearTerminal();
    currentPage = nextPage;
    if(currentPage)
        currentPage->Load();
    else
        throw std::runtime_error("Page can't be loaded!");
}

Page* PageManager::getPage(const std::string& pageKey){
    auto it = allPages.find(pageKey);
    if(it != allPages.end())
        return it->second.get();
    return nullptr;
}
