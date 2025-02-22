#include "Objects.h"

namespace objects
{
    BOOL* const gIsWindowedMode = (BOOL*)(0x00946530);

    ATOM* const gWindowClassID = (ATOM*)(0x009874C8);

    HWND* const gWindowHandle_0 = (HWND*)(0x009874C4);

    HWND* const gWindowHandle_1 = (HWND*)(0x00971F98);

    CHAR* const gWindowName = (CHAR*)(0x0092290C);

    LPDIRECT3D9* const gD3D = (LPDIRECT3D9*)(0x00971FA4);

    LPDIRECT3DDEVICE9* const gD3DDevice = (LPDIRECT3DDEVICE9*)(0x00971F94);
}