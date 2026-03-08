#pragma once

#include "Page/page.h"

class ModifyPage : public Page{
    public:
        ModifyPage();
        
        void Load() override;
        
        void initNeighbourPages() override;
};
