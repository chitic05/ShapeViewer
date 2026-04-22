#pragma once

#include "Page/page.h"

class DeletePage final : public Page
{
public:
    DeletePage();

    void Load() override;

    void initNeighbourPages() override;
};