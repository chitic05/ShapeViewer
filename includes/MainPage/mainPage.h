#pragma once

#include "Page/page.h"

class MainPage final : public Page
{
public:
    MainPage();

    void Load() override;

    void initNeighbourPages() override;
};