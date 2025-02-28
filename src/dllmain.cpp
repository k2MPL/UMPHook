#include <Windows.h>
#include <WinUser.h>

#include <stdio.h>

#include "Bink32Forwards.h"

#include "FunctionsDecompiled.h"
#include "Functions.h"
#include "Objects.h"

#include <MinHook.h>

#define UNUSED_RETURN(FUNC) (void)FUNC

class WindowedModeModule
{
private:
    static RegisterGameWindowClass_Decl(RegisterWindowClass)
    {
        WndProc_Original = _wndProc;
         
        if (*objects::gWindowClassID)
            UnregisterClassA(_lpClassName, _hInstance);

        WNDCLASSEXA desc;
        ZeroMemory(&desc, sizeof(desc));

        desc.lpfnWndProc = WndProc;
        desc.cbSize = sizeof(WNDCLASSEXA);
        desc.style = CS_CLASSDC;
        desc.hInstance = _hInstance;
        desc.lpszClassName = _lpClassName;

        if (_iconResourceID)
        {
            desc.hIcon = LoadIconA(_hInstance, MAKEINTRESOURCEA(_iconResourceID));
        }

        ATOM result = RegisterClassExA(&desc);
        *objects::gWindowClassID = result;

        return result;
    }

    static CreateGameWindow_Decl(CreateGameWindow)
    {
        return CreateGameWindow_Trampoline(_lpClassName, _lpWindowName, _hInstance, _x, _y, _width, _height, FALSE);
    }

    static CreateD3D_Decl(CreateD3D)
    {
        *objects::gIsWindowedMode = TRUE;
        return CreateD3D_Trampoline(_hWnd);
    }
   
    static LRESULT __stdcall WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
    {
        return WndProc_Original(_hWnd, _uMsg, _wParam, _lParam);
    }

public:
    static void Init()
    {
        MH_CreateHook(functions::RegisterGameWindowClass, RegisterWindowClass, (LPVOID*)&RegisterGameWindowClass_Trampoline);
        MH_EnableHook(functions::RegisterGameWindowClass);

        MH_CreateHook(functions::CreateGameWindow, CreateGameWindow, (LPVOID*)&CreateGameWindow_Trampoline);
        MH_EnableHook(functions::CreateGameWindow);

        MH_CreateHook(functions::CreateD3D, CreateD3D, (LPVOID*)&CreateD3D_Trampoline);
        MH_EnableHook(functions::CreateD3D);
    }

private:
    static WNDPROC WndProc_Original;

    static functions::RegisterGameWindowClass_t RegisterGameWindowClass_Trampoline;
    static functions::CreateGameWindow_t CreateGameWindow_Trampoline;
    static functions::CreateD3D_t CreateD3D_Trampoline;
};

WNDPROC WindowedModeModule::WndProc_Original{ nullptr };

functions::RegisterGameWindowClass_t WindowedModeModule::RegisterGameWindowClass_Trampoline{ nullptr };
functions::CreateGameWindow_t WindowedModeModule::CreateGameWindow_Trampoline{ nullptr };
functions::CreateD3D_t WindowedModeModule::CreateD3D_Trampoline{ nullptr };

struct StartupOptions
{
    bool enableDecompiled{ false };
    bool enableWindowModule{ false };
};

StartupOptions gStartupOptions;

void ReadStartupOptions()
{
    // CMD:
    // -eDecomp
    // -eWnd

    //#TODO: parse cmd line

    gStartupOptions.enableDecompiled = false;
    gStartupOptions.enableWindowModule = true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            if (MH_Initialize() == MH_OK)
            {
                AllocConsole();

                UNUSED_RETURN(freopen("CONOUT$", "w", stdout));
                UNUSED_RETURN(freopen("CONOUT$", "w", stderr));

                ReadStartupOptions();

                if (gStartupOptions.enableDecompiled)
                {
                    FunctionsDecompiledModule::Init();
                }
                else
                {
                    if (gStartupOptions.enableWindowModule)
                        WindowedModeModule::Init();
                }
            }
        }
        break;

        case DLL_THREAD_ATTACH:
        {
        }
        break;

        case DLL_THREAD_DETACH:
        {
        }
        break;

        case DLL_PROCESS_DETACH:
        {
        }
        break;

        default:
            break;
    }

    return TRUE;
}

