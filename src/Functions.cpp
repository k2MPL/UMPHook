#include "Functions.h"

namespace functions
{
    USMWinMain_t const USMWinMain = (USMWinMain_t)(0x005AC1E0);

    RegisterClassAndCreateWindow_t const RegisterClassAndCreateWindow = (RegisterClassAndCreateWindow_t)(0x0081C140);

    RegisterGameWindowClass_t const RegisterGameWindowClass = (RegisterGameWindowClass_t)(0x0081BFB0);

    CreateGameWindow_t const CreateGameWindow = (CreateGameWindow_t)(0x0081C030);
    
    CreateD3D_t const CreateD3D = (CreateD3D_t)(0x0076D680);

    FSOpenFile_t const FSOpenFile = (FSOpenFile_t)(0x0079FF10);

    AllocateAlignedMemory_t const AllocateAlignedMemory = (AllocateAlignedMemory_t)(0x0058EC30);

    FreeAlignedMemory_t const FreeAlignedMemory = (FreeAlignedMemory_t)(0x0058EC80);

    AllocateMemory_t const AllocateMemory = (AllocateMemory_t)(0x00535780);

    FreeMemory_t const FreeMemory = (FreeMemory_t)(0x0058EB70);
}