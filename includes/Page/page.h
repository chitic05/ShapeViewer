#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Page
{

public:
    Page();

    virtual void initNeighbourPages() = 0;

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