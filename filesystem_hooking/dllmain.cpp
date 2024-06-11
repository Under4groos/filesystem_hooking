// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "Converter.h"
#include "Console.h"


 
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:


        CreateConsole();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        CloseConsole();
        break;
    }
    return TRUE;
}

