#include "stdafx.h"

#include "dinput8\dinputWrapper.h"
#include "d3d9\d3d9Wrapper.h"
#include "DSNA.h"

// Export DINPUT8
tDirectInput8Create oDirectInput8Create;

// Export D3D9
tDirect3DCreate9 oDirect3DCreate9;

BOOL InitInstance(HMODULE hModule)
{
    MessageBox(0, "DSNA is enabled.", "Dark Souls Networking Arbiter", MB_OK);

    log_info("Dark Souls Networking Arbiter");

    // Load the real dll
    HMODULE hMod;
    char dllPath[MAX_PATH];

    GetSystemDirectory(dllPath, MAX_PATH);
    strcat_s(dllPath, "\\dinput8.dll");
    hMod = LoadLibrary(dllPath);
    oDirectInput8Create = (tDirectInput8Create)GetProcAddress(hMod, "DirectInput8Create");

    GetSystemDirectory(dllPath, MAX_PATH);
    strcat_s(dllPath, "\\d3d9.dll");
    hMod = LoadLibrary(dllPath);
    oDirect3DCreate9 = (tDirect3DCreate9)GetProcAddress(hMod, "Direct3DCreate9");
    
    // Call the main thread
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&Begin, hModule, 0, nullptr);

    return true;
}

BOOL ExitInstance()
{
    End();
    log_info("Dark Souls Networking Arbiter");

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        InitInstance(hModule);
        break;
    case DLL_PROCESS_DETACH:
        ExitInstance();
        break;
    }
    return TRUE;
}

