#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Clasă abstractă - nu poate fi instantiată direct
// Conține cel puțin 2 funcții pur virtuale
class Page
{

public:
    Page();

    // Funcție pur virtuală - trebuie suprascrisă în clasele derivate
    virtual void initNeighbourPages() = 0;

    // Funcție pur virtuală - trebuie suprascrisă în clasele derivate
    virtual void Load() = 0;

    std::string getName();

    std::string getKey();

    Page *getPrevious();

    void changePage(Page *page);

    virtual ~Page();

protected:
    const char *pageName;

    std::string pageKey;

    Page *previous;

    Page** next;

    std::string text;
};