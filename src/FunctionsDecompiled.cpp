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

    /*static void __cdecl PAKUnknown(void* _p1, types::Platform _platform)
    {
        const char* platformsPAK[] =
        {
            ".PAK",
            "_XB.PAK",
            "_GC.PAK",
            "_PC.PAK"
        };
    }*/
}

class USMString
{
    typedef void*(*__thiscall V0Constructor_0_t)(void*);
    static constexpr V0Constructor_0_t const V0Constructor_0 = (V0Constructor_0_t)(0x00420F00);

    typedef void* (*__thiscall V0Constructor_1_t)(void*, const char*);
    static constexpr V0Constructor_1_t const V0Constructor_1 = (V0Constructor_1_t)(0x00421100);

    typedef void(*__thiscall V0Constructor_2_t)(void*, USMString*);
    static constexpr V0Constructor_2_t const V0Constructor_2 = (V0Constructor_2_t)(0x0041FE10);

    typedef void(*__thiscall V0Destructor_0_t)(void*, int);
    static constexpr V0Destructor_0_t const V0Destructor_0 = (V0Destructor_0_t)(0x004209C0);

    static constexpr size_t RequiredClassSize = 16;

public:
    static void* __fastcall Constructor_0(void* _this, void* _unused)
    {
        USMString* thisPtr = (USMString*)_this;
        thisPtr->p0 = 0;
        thisPtr->p1_StrLen = 0;
        thisPtr->p2_Str = objects::gNullString;
        thisPtr->p3_Allocation = NULL;

        ++(*objects::g_00957CEC);

        return _this;
    }

    static void* __fastcall Constructor_1(void* _this, void* _unused, const char* _str)
    {
        USMString* thisPtr = (USMString*)_this;
        thisPtr->p0 = 0;
        thisPtr->p1_StrLen = 0;
        thisPtr->p2_Str = objects::gNullString;
        thisPtr->p3_Allocation = NULL;

        ++(*objects::g_00957CEC);

        if (_str)
        {
            sub_41F9D0(_this, _unused, _str, -1);
        }

        return _this;
    }

    static void* Constructor_2(void* _this, void* _unused, USMString* _copy)
    {
        USMString* thisPtr = (USMString*)_this;
        if (thisPtr != _copy)
        {
            sub_41F9D0(_this, _unused, thisPtr->p2_Str, thisPtr->p1_StrLen);
        }

        return _this;
    }

    static void _fastcall Destructor_0(void* _this, void* _unused, int _unknownValue)
    {
        //#TODO: sub_41F970(_this, _unused);
        --(*objects::g_00957CEC);
    }

    static int __fastcall sub_41F9D0(void* _this, void* _unused, const char* _str, int _strLen)
    {
        USMString* thisPtr = (USMString*)_this;

        if (_strLen == -1)
        {
            _strLen = strlen(_str);
        }

        int result = 0;

        if (_strLen > thisPtr->p1_StrLen)
        {
            //#TODO: sub_41F970(_this, _unused);

            char* resultStr = NULL;
            if (_strLen >= 0xB0) // 176
            {
                resultStr = new char(_strLen + 1);
            }
            else
            {
                //#TODO: resultStr = sub_59F750(_strLen + 1, &_thisPtr->p3)
            }

            thisPtr->p2_Str = resultStr;
        }

        if (_strLen <= 0)
        {
            //#TODO: sub_41F970(_this, _unused);

            thisPtr->p1_StrLen = _strLen;
            thisPtr->p2_Str = objects::gNullString;
        }
        else
        {
            assert(thisPtr->p2_Str != objects::gNullString && "Can't write to NullString");
            assert(thisPtr->p2_Str != NULL && "String buffer is not allocated");

            memcpy(thisPtr->p2_Str, _str, _strLen + 1);
        }

        return result;
    }

    static void Init()
    {
        assert(sizeof(USMString) == RequiredClassSize);
    }

public:
    DWORD p0; // this
    int p1_StrLen; // this + 4/0x4. Info: p2 length (#TODO: Clarify)
    char* p2_Str; // this + 8/0x8 
    void* p3_Allocation; // this + 12/0xC
};

class USMFile
{
    typedef void(*__thiscall V1Constructor_0_t)(void*);
    static constexpr V1Constructor_0_t const V1Constructor_0 = (V1Constructor_0_t)(0x0058DEA0);

    static constexpr size_t RequiredClassSize = 52;

public:
    static void* __fastcall Constructor_0(void* _this, void* _unused)
    {
        USMFile* thisPtr = (USMFile*)_this;
        
        USMString::Constructor_0(&thisPtr->p0_FileName, NULL);

        thisPtr->p4 = 0;
        thisPtr->p5 = FALSE;
        thisPtr->p6 = FALSE;
        thisPtr->p7_FileHandle = INVALID_HANDLE_VALUE;
        thisPtr->p8_CurrentFilePointer = 0;
        thisPtr->p9 = *objects::g_00965E69;
        thisPtr->p10 = -1;
        thisPtr->p11 = 0;
        thisPtr->p12 = 0;

        return _this;
    }

    static void Init()
    {
        assert(sizeof(USMFile) == RequiredClassSize);
    }

public:
    USMString p0_FileName; // this
    DWORD p4; // this + 16/0x10
    BYTE p5; // this + 20/0x14
    BYTE p6; // this + 21/0x15
    BYTE padding_0[2];
    HANDLE p7_FileHandle; // this + 24/0x18
    DWORD p8_CurrentFilePointer; // this + 28/0x1C
    DWORD padding_1; // this + 32/0x50 #TODO: Skipped 4 bytes/or unitialized field? 
    BYTE p9; // this + 36/0x24
    BYTE padding_2[3];
    int p10; // this + 40/0x28
    DWORD p11; // this + 44/0x2C
    DWORD p12; // this + 48/0x30
};

struct AmalgapakHeader
{
    DWORD p0;
    DWORD p1;
    DWORD p2;
    DWORD p3;
    DWORD p4;
    DWORD p5;
    DWORD p6;

    DWORD p7_FilePointer_1;
    DWORD p8_MemSize_1;

    DWORD p9_FilePointer_3;
    DWORD p10_MemSize_3;

    DWORD p11_FilePointer_2;
    DWORD p12_MemSize_2;

    DWORD p13;
};

void FunctionsDecompiledModule::Init()
{
#if 1
    USMString::Init();
    USMFile::Init();
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
