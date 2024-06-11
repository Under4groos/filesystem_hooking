#pragma once
#include "pch.h"
void CreateConsole() {
    if (!AllocConsole()) {
       
        return;
    }
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
}

void CloseConsole() {
    FreeConsole();
}