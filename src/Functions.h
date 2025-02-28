#pragma once

#include <Windows.h>

namespace functions
{
    // Windown & D3D

    #define USMWinMain_Decl(NAME) int __stdcall NAME(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nShowCmd)
    typedef int(*__stdcall USMWinMain_t)(HINSTANCE, HINSTANCE, LPSTR, int);
    extern USMWinMain_t const USMWinMain;

    #define RegisterClassAndCreateWindow_Decl(NAME) HWND __cdecl NAME(LPCSTR _lpClassName, LPCSTR _lpWindowName, int _x, int _y, int _width, int _height, WNDPROC _wndProc, HINSTANCE _hInstance, int _iconResourceID, BOOL _isFullScreen)
    typedef HWND(*__cdecl RegisterClassAndCreateWindow_t)(LPCSTR, LPCSTR, int, int, int, int, WNDPROC, HINSTANCE, int, BOOL);
    extern RegisterClassAndCreateWindow_t const RegisterClassAndCreateWindow;

    #define RegisterGameWindowClass_Decl(NAME) ATOM __cdecl NAME(LPCSTR _lpClassName, WNDPROC _wndProc, HINSTANCE _hInstance, int _iconResourceID)
    typedef ATOM(*__cdecl RegisterGameWindowClass_t)(LPCSTR, WNDPROC, HINSTANCE, int);
    extern RegisterGameWindowClass_t const RegisterGameWindowClass;

    #define CreateGameWindow_Decl(NAME) HWND __cdecl NAME(LPCSTR _lpClassName, LPCSTR _lpWindowName, HINSTANCE _hInstance, int _x, int _y, int _width, int _height, BOOL _isFullScreen)
    typedef HWND(*__cdecl CreateGameWindow_t)(LPCSTR, LPCSTR, HINSTANCE, int, int, int, int, BOOL);
    extern CreateGameWindow_t const CreateGameWindow;
    
    #define CreateD3D_Decl(NAME) HRESULT __cdecl NAME(HWND _hWnd)
    typedef HRESULT(*__cdecl CreateD3D_t)(HWND);
    extern CreateD3D_t const CreateD3D;

    // File system

    #define FSOpenFile_Decl(NAME) DWORD __cdecl NAME(HANDLE* _hResult, LPCSTR _lpFileName, DWORD _flags, LARGE_INTEGER _distanceToMove)
    typedef DWORD(*__cdecl FSOpenFile_t)(HANDLE*, LPCSTR, DWORD, LARGE_INTEGER);
    extern FSOpenFile_t const FSOpenFile;

    // Memory

    #define AllocateAlignedMemory_Decl(NAME) void* __cdecl NAME(size_t _alignment, size_t _size)
    typedef void* (*__cdecl AllocateAlignedMemory_t)(size_t, size_t);
    extern AllocateAlignedMemory_t const AllocateAlignedMemory;

    #define FreeAlignedMemory_Decl(NAME) void __cdecl NAME(void* _buffer)
    typedef void(*__cdecl FreeAlignedMemory_t)(void*);
    extern FreeAlignedMemory_t const FreeAlignedMemory;

    #define AllocateMemory_Decl(NAME) void* __cdecl NAME(size_t _size) 
    typedef void* (*__cdecl AllocateMemory_t)(size_t);
    extern AllocateMemory_t const AllocateMemory;

    #define FreeMemory_Decl(NAME) void __cdecl FreeMemory(void* _buffer)
    typedef void(*__cdecl FreeMemory_t)(void*);
    extern FreeMemory_t const FreeMemory;
}