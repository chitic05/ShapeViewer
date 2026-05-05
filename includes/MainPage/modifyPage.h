#pragma once

#include "Page/page.h"

// final - previne ereditarea din ModifyPage
// VALID: ModifyPage e endpoint in ierarhia Page (nu se mai mosteneste)
// INVALID: Nu se poate face: class SpecialModifyPage : public ModifyPage { }
class ModifyPage final : public Page
{
public:
    ModifyPage();

    void Load() override;

    void initNeighbourPages() override;
};
