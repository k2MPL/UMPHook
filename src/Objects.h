#pragma once

#include <Windows.h>

#include <d3d9.h>

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
}