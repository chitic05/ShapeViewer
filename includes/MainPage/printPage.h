#pragma once

#include "Page/page.h"

// final - previne ereditarea din PrintPage
// VALID: PrintPage e endpoint in ierarhia Page (nu se mai mosteneste)
// INVALID: Nu se poate face: class SpecialPrintPage : public PrintPage { }
class PrintPage final : public Page
{
public:
    PrintPage();

    void Load() override;

    void initNeighbourPages() override;
};