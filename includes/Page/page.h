#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Page
{

public:
    virtual void initNeighbourPages() = 0;

    virtual void Load() = 0;

    virtual std::string getName();

    virtual std::string getKey();

    virtual Page *getPrevious();

    void changePage(Page *page);

    virtual ~Page();

protected:
    const char *pageName;

    std::string pageKey;

    Page *previous;

    std::vector<Page *> next;

    std::string text;
};