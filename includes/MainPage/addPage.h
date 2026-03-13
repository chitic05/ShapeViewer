#pragma once

#include "Page/page.h"

class AddPage : public Page
{
public:
    AddPage();

    void Load() override;

    void initNeighbourPages() override;
};