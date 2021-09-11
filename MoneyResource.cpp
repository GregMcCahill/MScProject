#include "pch.h"
#include <Windows.h>
#include <iostream> 



DWORD WINAPI MyThread(HMODULE hModule)
{
    
    AllocConsole();
    FILE* f = new FILE;
    freopen_s(&f, "CONOUT$", "w", stdout);

    
    std::cout << "Process ID is: " << GetCurrentProcessId() << std::endl;

    // resources memory address is at: [[[[[["game.dat+009E4AD4]+14]+0]+8]+C0]+8]+94
    //these lines follow the pointer path

    uintptr_t Bfme2Addr = (uintptr_t)GetModuleHandle(L"game.dat");
    printf("Bfme2Addr: %p\n", Bfme2Addr);
    uintptr_t firstStep = *(uintptr_t*)(Bfme2Addr + 0x009E4AD4);
    printf("Bmfe2Addr + 0x18FCD60 = %p has value %p\n", Bfme2Addr + 0x18FCD60, firstStep);
    uintptr_t secondStep = *(uintptr_t*)(firstStep + 0x14);
    printf("firstStep + 0x14 = %p has value %p\n", firstStep + 0x14, secondStep);
    uintptr_t thirdStep = *(uintptr_t*)(secondStep + 0x0);
    printf("secondStep + 0x0 = %p has value %p\n", secondStep + 0x0, thirdStep);
    uintptr_t forthStep = *(uintptr_t*)(thirdStep + 0x8);
    printf("thirdStep + 0x8 = %p has value %p\n", thirdStep + 0x8, forthStep);
    uintptr_t fifthStep = *(uintptr_t*)(forthStep + 0xC0);
    printf("forthStep + 0xC0 = %p has value %p\n", forthStep + 0x0, fifthStep);
    uintptr_t sixthStep = *(uintptr_t*)(fifthStep + 0x8);
    printf("fifthStep + 0x8 = %p has value %p\n", fifthStep + 0x8, sixthStep);


    int* resourcesAddr = (int*)(sixthStep + 0x94);
    int resources = *resourcesAddr;


    while (true) {
        if (resources != *resourcesAddr) {
            resources = *resourcesAddr;
            std::cout << "Resources: " << resources << std::endl;
        }

        //when the player presses M increases resources by 10,000
        if (GetAsyncKeyState('M') & 1) {
            std::cout << "   M key pressed";
            *resourcesAddr = *resourcesAddr + 10000;
        }

    }

    return 0;
}







BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MyThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}