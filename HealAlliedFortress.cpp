#include "pch.h"
#include <Windows.h>
#include <iostream> 



DWORD WINAPI MyThread(HMODULE hModule)
{
    
    AllocConsole();
    FILE* f = new FILE;
    freopen_s(&f, "CONOUT$", "w", stdout);

   
    std::cout << "Process ID is: " << GetCurrentProcessId() << std::endl;

    // current health of the players fortress' memory address is at: [[[[[[["game.dat+009E4AD4]+14]+0]+38]+E0]+18]+8]+AF0
    //these lines follow the pointer path

    uintptr_t Bfme2Addr = (uintptr_t)GetModuleHandle(L"game.dat");
    printf("Bfme2Addr: %p\n", Bfme2Addr);
    uintptr_t firstStep = *(uintptr_t*)(Bfme2Addr + 0x009E4AD4);
    printf("Bmfe2Addr + 0x18FCD60 = %p has value %p\n", Bfme2Addr + 0x18FCD60, firstStep);

    uintptr_t secondStep = *(uintptr_t*)(firstStep + 0x14);
    printf("firstStep + 0x14 = %p has value %p\n", firstStep + 0x14, secondStep);

    uintptr_t thirdStep = *(uintptr_t*)(secondStep + 0x0);
    printf("secondStep + 0x0 = %p has value %p\n", secondStep + 0x0, thirdStep);

    uintptr_t forthStep = *(uintptr_t*)(thirdStep + 0x38);
    printf("thirdStep + 0x38 = %p has value %p\n", thirdStep + 0x38, forthStep);

    uintptr_t fifthStep = *(uintptr_t*)(forthStep + 0xE0);
    printf("forthStep + 0xE0 = %p has value %p\n", forthStep + 0xE0, fifthStep);

    uintptr_t sixthStep = *(uintptr_t*)(fifthStep + 0x18);
    printf("fifthStep + 0x18 = %p has value %p\n", fifthStep + 0x18, sixthStep);

    uintptr_t seventhStep = *(uintptr_t*)(sixthStep + 0x8);
    printf("sixthStep + 0x8 = %p has value %p\n", sixthStep + 0x8, seventhStep);


    float* playerFortHealthAddr = (float*)(seventhStep + 0xAF0);
    float playerFortHealth = *playerFortHealthAddr;


    while (true) {
        if (playerFortHealth != *playerFortHealthAddr) {
            playerFortHealth = *playerFortHealthAddr;
            std::cout << "Fortress Health: " << playerFortHealth << std::endl;
        }

        //when the player presses H they heal the fortress by 500
        if (GetAsyncKeyState('H') & 1) {
            std::cout << "   H key pressed";
            *playerFortHealthAddr = *playerFortHealthAddr + 500;
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

