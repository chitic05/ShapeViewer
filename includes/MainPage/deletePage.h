#pragma once

#include "Page/page.h"

// final - previne ereditarea din DeletePage
// VALID: DeletePage e endpoint in ierarhia Page (nu se mai mosteneste)
// INVALID: Nu se poate face: class SpecialDeletePage : public DeletePage { }
class DeletePage final : public Page
{
public:
    DeletePage();

    void Load() override;

    void initNeighbourPages() override;
};