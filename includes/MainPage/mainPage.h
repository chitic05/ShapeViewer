#pragma once

#include "Page/page.h"

class MainPage : public Page{
    public:
        MainPage();
        void Load() override;
        void initNeighbourPages() override;
};