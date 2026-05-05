#pragma once

#include "Page/page.h"

// final - previne ereditarea din AddPage
// VALID: AddPage e endpoint in ierarhia Page (nu se mai mosteneste)
// INVALID: Nu se poate face: class SpecialAddPage : public AddPage { }
class AddPage final : public Page
{
public:
    AddPage();

    void Load() override;

    void initNeighbourPages() override;
};