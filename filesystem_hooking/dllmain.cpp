// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
 
#include "Console.h"
#include <Windows.h>
#include <iostream>
using namespace std;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateConsole();

        cout << GetModuleHandleW(NULL) << endl;

        /*NTSTATUS nt = RhInjectLibrary(
            processId,
            0,
            EASYHOOK_INJECT_DEFAULT,
            NULL,
            dllToInject,
            NULL,
            0
        );*/



    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        CloseConsole();
        break;
    }
    return TRUE;
}

