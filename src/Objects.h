#pragma once

#include <Windows.h>

#include <d3d9.h>

#include "Types.h"

namespace objects
{
    extern BOOL* const gIsWindowedMode;

    extern ATOM* const gWindowClassID;

    // Created and initialized by CreateWindow func., assigned in CreateWindow func.
    extern HWND* const gWindowHandle_0;

    // Created and initialized by CreateD3D func. (in case if window was not created before this call), assigned in CreateD3D func.
    extern HWND* const gWindowHandle_1;

    extern CHAR* const gWindowName;

    extern LPDIRECT3D9* const gD3D;

    extern LPDIRECT3DDEVICE9* const gD3DDevice;

    //#TODO: Investigate: maybe field part of bigger 'statictics' struct
    //#TODO: Maybe change type to int. Possible negative values?
    extern DWORD* const gTotalMemoryAllocated;

    // This is set during boot time. Value is 3 for PC platform. Used as offset for different arrays
    extern types::Platform* const gArchivePlatformIndex;

    extern const char* const gNullString;

    // --- Unknown but used ---

    extern int* const g_00957CEC;

    extern BYTE* const g_00965E69;
}