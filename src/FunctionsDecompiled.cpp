#include "FunctionsDecompiled.h"
#include "Functions.h"
#include "Objects.h"

#include <MinHook.h>

#include <assert.h>

// This is 1 to 1 decompilation of game functions. Not used, just for reference

namespace decompiled
{
    static RegisterGameWindowClass_Decl(RegisterGameWindowClass)
    {
        if (*objects::gWindowClassID)
            UnregisterClassA(_lpClassName, _hInstance);

        WNDCLASSEXA desc;
        ZeroMemory(&desc, sizeof(desc));

        desc.lpfnWndProc = _wndProc;
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

    static FSOpenFile_Decl(FSOpenFile)
    {
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

    static void* __cdecl AllocateAlignedMemory(size_t _alignment, size_t _size)
    {
        void* result = _aligned_malloc(_size, _alignment);
        if (result)
        {
            DWORD v1 = ((DWORD)result & 0xFFFFFFFC);
            v1 -= 0x8; //#TODO: WTF? Btw. original bin has 0x4, but it doesn't work here (maybe cuz. USM is using Visual C++ 2003 runtime, but dll is using modern one). Need to use VC2003 runtime somehow

            DWORD* m1 = (DWORD*)v1;
            DWORD* m2 = (DWORD*)(*m1);

            *objects::gTotalMemoryAllocated += _msize(m2);
        }

        return result;
    }

    static void __cdecl FreeAlignedMemory(void* _buffer)
    {
        if (_buffer)
        {
            DWORD v1 = ((DWORD)_buffer & 0xFFFFFFFC);
            v1 -= 0x8; //#TODO: WTF? Btw. original bin has 0x4, but it doesn't work here (maybe cuz. USM is using Visual C++ 2003 runtime, but dll is using modern one). Need to use VC2003 runtime somehow

            DWORD* m1 = (DWORD*)v1;
            DWORD* m2 = (DWORD*)(*m1);

            *objects::gTotalMemoryAllocated -= _msize(m2);
            _aligned_free(_buffer);
        }
    }

    static void* __cdecl AllocateMemory(size_t _size)
    {
        //#TODO: Find out what this byte values are

        char* byte_9224F0 = (char*)(0x009224F0);
        char* byte_9224E8 = (char*)(0x009224E8);

        if (*byte_9224F0)
        {
            if (*byte_9224E8)
            {
                *byte_9224E8 = 0;
            }

            *byte_9224F0 = 0;
        }

        void* result = malloc(_size);
        *objects::gTotalMemoryAllocated += _msize(result);

        return result;
    }

    static void __cdecl FreeMemory(void* _buffer)
    {
        if (_buffer)
        {
            *objects::gTotalMemoryAllocated -= _msize(_buffer);
            free(_buffer);
        }
    }

    static void __cdecl PAKUnknown(void* _p1, types::Platform _platform)
    {
        const char* platformsPAK[] =
        {
            ".PAK",
            "_XB.PAK",
            "_GC.PAK",
            "_PC.PAK"
        };
    }
}

class V0Class
{
    typedef void(*__thiscall V0Constructor_0_t)(void*);
    static constexpr V0Constructor_0_t const V0Constructor_0 = (V0Constructor_0_t)(0x00420F00);

    static constexpr size_t RequiredClassSize = 16;

public:
    static void* __fastcall Constructor_0(void* _this, void* _unused)
    {
        V0Class* data = (V0Class*)_this;
        data->p0 = 0;
        data->p1 = 0;
        data->p2_Str = objects::gNullString;
        data->p3 = 0;

        ++(*objects::g_00957CEC);

        return _this;
    }

    static void* __fastcall Constructor_1(void* _this, void* _unused, const char* _str)
    {
        V0Class* data = (V0Class*)_this;
        data->p0 = 0;
        data->p1 = 0;
        data->p2_Str = objects::gNullString;
        data->p3 = 0;

        ++(*objects::g_00957CEC);

        if (_str)
        {
            sub_41F9D0(_this, _unused, _str, -1);
        }

        return _this;
    }

    static int __fastcall sub_41F9D0(void* _this, void* _unused, const char* _str, int _strLen)
    {
        V0Class* thisPtr = (V0Class*)_this;

        if (_strLen == -1)
        {
            _strLen = strlen(_str);
        }

        int result = 0;

        if (_strLen > thisPtr->p1)
        {

        }

        if (_strLen <= 0)
        {

        }
        else
        {

        }

        return result;
    }

    static void Init()
    {
        assert(sizeof(V0Class) == RequiredClassSize);

        MH_CreateHook(V0Constructor_0, V0Class::Constructor_0, NULL);
        MH_EnableHook(V0Constructor_0);
    }

public:
    DWORD p0; // this
    int p1; // this + 4/0x4. Info: p2 length (#TODO: Clarify)
    const char* p2_Str; // this + 8/0x8 
    DWORD p3; // this + 12/0xC
};

class V1Class : public V0Class
{
    using Parent_t = V0Class;

    typedef void(*__thiscall V1Constructor_0_t)(void*);
    static constexpr V1Constructor_0_t const V1Constructor_0 = (V1Constructor_0_t)(0x0058DEA0);

    static constexpr size_t RequiredClassSize = 52;

public:
    static void* __fastcall Constructor_0(void* _this, void* _unused)
    {
        Parent_t::Constructor_0(_this, _unused);

        V1Class* data = (V1Class*)_this;
        data->p4 = 0;
        data->p5 = FALSE;
        data->p6 = FALSE;
        data->p7_FileHandle = INVALID_HANDLE_VALUE;
        data->p8 = 0;
        data->p9 = *objects::g_00965E69;
        data->p10 = -1;
        data->p11 = 0;
        data->p12 = 0;

        return _this;
    }

    static void Init()
    {
        assert(sizeof(V1Class) == RequiredClassSize);

        MH_CreateHook(V1Constructor_0, V1Class::Constructor_0, NULL);
        MH_EnableHook(V1Constructor_0);
    }

public:
    DWORD p4; // this + 16/0x10
    BYTE p5; // this + 20/0x14
    BYTE p6; // this + 21/0x15
    BYTE padding_0[2];
    HANDLE p7_FileHandle; // this + 24/0x18
    DWORD p8; // this + 28/0x1C
    DWORD padding_1; // this + 32/0x50 #TODO: Skipped 4 bytes/or unitialized field? 
    BYTE p9; // this + 36/0x24
    BYTE padding_2[3];
    int p10; // this + 40/0x28
    DWORD p11; // this + 44/0x2C
    DWORD p12; // this + 48/0x30
};

void FunctionsDecompiledModule::Init()
{
#if 1
    V0Class::Init();
    V1Class::Init();
#else
    MH_CreateHook(functions::RegisterGameWindowClass, decompiled::RegisterGameWindowClass, NULL);
    MH_EnableHook(functions::RegisterGameWindowClass);

    MH_CreateHook(functions::FSOpenFile, decompiled::FSOpenFile, NULL);
    MH_EnableHook(functions::FSOpenFile);

    MH_CreateHook(functions::AllocateAlignedMemory, decompiled::AllocateAlignedMemory, NULL);
    MH_EnableHook(functions::AllocateAlignedMemory);

    MH_CreateHook(functions::FreeAlignedMemory, decompiled::FreeAlignedMemory, NULL);
    MH_EnableHook(functions::FreeAlignedMemory);

    MH_CreateHook(functions::AllocateMemory, decompiled::AllocateMemory, NULL);
    MH_EnableHook(functions::AllocateMemory);

    MH_CreateHook(functions::FreeMemory, decompiled::FreeMemory, NULL);
    MH_EnableHook(functions::FreeMemory);
#endif
}
