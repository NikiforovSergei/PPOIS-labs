#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include "Header.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <Psapi.h>

using namespace std;

LONG WINAPI VEH(EXCEPTION_POINTERS* e)
{
    PVOID exeption_adress = e->ExceptionRecord->ExceptionAddress;

    if (exeption_adress != 0)
    {
        DWORD exeption_id = e->ExceptionRecord->ExceptionCode;
        string exeption = "Exeption handled at 0x" + to_string((DWORD)exeption_adress) + " exeption id " + to_string(exeption_id);
        MessageBoxA(0, exeption.c_str(), "Error", MB_ICONERROR);
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
    AddVectoredExceptionHandler(1, VEH);

    ImportOcean field;
    field.activate();
}