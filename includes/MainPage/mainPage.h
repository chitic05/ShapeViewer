#pragma once

#include "Page/page.h"

// final - previne ereditarea din MainPage
// VALID: MainPage e endpoint in ierarhia Page (nu se mai mosteneste)
// INVALID: Nu se poate face: class SpecialMainPage : public MainPage { }
class MainPage final : public Page
{
public:
    MainPage();

    void Load() override;

    void initNeighbourPages() override;
};