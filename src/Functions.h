#pragma once

#include <Windows.h>

namespace functions
{
    #define USMWinMain_Decl(NAME) int __stdcall NAME(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nShowCmd)
    typedef int(* __stdcall USMWinMain_t)(HINSTANCE, HINSTANCE, LPSTR, int);
    extern USMWinMain_t const USMWinMain;

    #define RegisterClassAndCreateWindow_Decl(NAME) HWND __cdecl NAME(LPCSTR _lpClassName, LPCSTR _lpWindowName, int _x, int _y, int _width, int _height, WNDPROC _wndProc, HINSTANCE _hInstance, int _iconResourceID, BOOL _isFullScreen)
    typedef HWND(* __cdecl RegisterClassAndCreateWindow_t)(LPCSTR, LPCSTR, int, int, int, int, WNDPROC, HINSTANCE, int, BOOL);
    extern RegisterClassAndCreateWindow_t const RegisterClassAndCreateWindow;

    #define RegisterGameWindowClass_Decl(NAME) ATOM __cdecl NAME(LPCSTR _lpClassName, WNDPROC _wndProc, HINSTANCE _hInstance, int _iconResourceID)
    typedef ATOM(* __cdecl RegisterGameWindowClass_t)(LPCSTR, WNDPROC, HINSTANCE, int);
    extern RegisterGameWindowClass_t const RegisterGameWindowClass;

    #define CreateGameWindow_Decl(NAME) HWND __cdecl NAME(LPCSTR _lpClassName, LPCSTR _lpWindowName, HINSTANCE _hInstance, int _x, int _y, int _width, int _height, BOOL _isFullScreen)
    typedef HWND(* __cdecl CreateGameWindow_t)(LPCSTR, LPCSTR, HINSTANCE, int, int, int, int, BOOL);
    extern CreateGameWindow_t const CreateGameWindow;

    #define CreateD3D_Decl(NAME) HRESULT __cdecl NAME(HWND _hWnd)
    typedef HRESULT(*__cdecl CreateD3D_t)(HWND);
    extern CreateD3D_t const CreateD3D;
}