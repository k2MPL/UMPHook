#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <WinUser.h>

#include <stdio.h>

#include "Bink32Forwards.h"

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

class FileSystemModule
{
private:
    static FSOpenFile_Decl(FSOpenFile)
    {
        printf("FileSystemModule::FSOpenFile: %s\n", _lpFileName);

        DWORD dwFlagsAndAttributes = _flags;
        dwFlagsAndAttributes <<= 0x1C;
        dwFlagsAndAttributes = ~dwFlagsAndAttributes;
        dwFlagsAndAttributes &= FILE_FLAG_NO_BUFFERING;
        dwFlagsAndAttributes |= FILE_FLAG_OVERLAPPED;

        DWORD dwCreationDisposition = _flags;
        dwCreationDisposition >>= 0x2;
        dwCreationDisposition = ~dwCreationDisposition;
        dwCreationDisposition &= CREATE_NEW;
        dwCreationDisposition |= CREATE_ALWAYS;

        DWORD dwShareMode = _flags;
        dwShareMode &= (FILE_SHARE_READ | FILE_SHARE_WRITE);

        //#TODO: Clarify. WTF is that magic with dwDesiredAccess...
        DWORD dwDesiredAccess = _flags;
        dwDesiredAccess &= 0x2;
        dwDesiredAccess |= (_flags << 2);
        dwDesiredAccess <<= 0x1D;

        HANDLE result = CreateFileA(_lpFileName, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
        if (result == INVALID_HANDLE_VALUE)
        {
            return GetLastError();
        }

        if (_flags & 0x4)
        {
            SetFilePointerEx(result, _distanceToMove, NULL, 0);
            SetEndOfFile(result);
            SetFilePointer(result, 0, NULL, 0);
        }

        *_hResult = result;
        return 0;
    }

public:
    static void Init()
    {
        MH_CreateHook(functions::FSOpenFile, FSOpenFile, (LPVOID*)&FSOpenFile_Trampoline);
        MH_EnableHook(functions::FSOpenFile);
    }

private:
    static functions::FSOpenFile_t FSOpenFile_Trampoline;
};

functions::FSOpenFile_t FileSystemModule::FSOpenFile_Trampoline{ nullptr };

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

                WindowedModeModule::Init();
                FileSystemModule::Init();
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

