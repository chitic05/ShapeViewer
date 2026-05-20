#pragma once

#include "Page/page.h"

class LogPage final : public Page
{
public:
    LogPage();

    void Load() override;
    void initNeighbourPages() override;
};
