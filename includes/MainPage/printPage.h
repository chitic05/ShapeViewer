#pragma once

#include "Page/page.h"

class PrintPage : public Page{
    public:
        PrintPage();
        
        void Load() override;
        
        void initNeighbourPages() override;
};