#include "pch.h"
#include <Windows.h>
#include <iostream> 



DWORD WINAPI MyThread(HMODULE hModule)
{
    
    AllocConsole();
    FILE* f = new FILE;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Process ID is: " << GetCurrentProcessId() << std::endl;

    // current health of the players fortress' memory address is at: [[[[[[["game.dat+009E4AB8]+14]+18]+14]+78]+98]+8]+C10
    //these lines follow the pointer path

    uintptr_t Bfme2Addr = (uintptr_t)GetModuleHandle(L"game.dat");
    printf("Bfme2Addr: %p\n", Bfme2Addr);
    uintptr_t firstStep = *(uintptr_t*)(Bfme2Addr + 0x009E4AB8);
    printf("Bmfe2Addr + 0x009E4AB8 = %p has value %p\n", Bfme2Addr + 0x009E4AB8, firstStep);

    uintptr_t secondStep = *(uintptr_t*)(firstStep + 0x14);
    printf("firstStep + 0x14 = %p has value %p\n", firstStep + 0x14, secondStep);

    uintptr_t thirdStep = *(uintptr_t*)(secondStep + 0x18);
    printf("secondStep + 0x18 = %p has value %p\n", secondStep + 0x18, thirdStep);

    uintptr_t forthStep = *(uintptr_t*)(thirdStep + 0x14);
    printf("thirdStep + 0x14 = %p has value %p\n", thirdStep + 0x14, forthStep);

    uintptr_t fifthStep = *(uintptr_t*)(forthStep + 0x78);
    printf("forthStep + 0x78 = %p has value %p\n", forthStep + 0x78, fifthStep);

    uintptr_t sixthStep = *(uintptr_t*)(fifthStep + 0x98);
    printf("fifthStep + 0x98 = %p has value %p\n", fifthStep + 0x98, sixthStep);

    uintptr_t seventhStep = *(uintptr_t*)(sixthStep + 0x8);
    printf("sixthStep + 0x8 = %p has value %p\n", sixthStep + 0x8, seventhStep);


    float* enemyFortHealthAddr = (float*)(seventhStep + 0xC10);
    float enemyFortHealth = *enemyFortHealthAddr;


    while (true) {
        if (enemyFortHealth != *enemyFortHealthAddr) {
            enemyFortHealth = *enemyFortHealthAddr;
            std::cout << "Fortress Health: " << enemyFortHealth << std::endl;
        }

        //when the player presses E they damage the enemy fortress by 500
        if (GetAsyncKeyState('E') & 1) {
            std::cout << "   E key pressed";
            *enemyFortHealthAddr = *enemyFortHealthAddr - 500;
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

