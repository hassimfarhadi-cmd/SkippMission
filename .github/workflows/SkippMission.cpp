
#include <windows.h>

DWORD WINAPI MainThread(LPVOID)
{
    const char* cheat = "SKIPMISSION";
    int position = 0;

    while (true)
    {
        for (int key = 'A'; key <= 'Z'; key++)
        {
            if (GetAsyncKeyState(key) & 1)
            {
                char pressed = (char)key;

                if (pressed == cheat[position])
                    position++;
                else
                    position = (pressed == cheat[0]) ? 1 : 0;

                if (cheat[position] == '\0')
                {
                    MessageBoxA(
                        NULL,
                        "SKIPMISSION detected!",
                        "SkipMission",
                        MB_OK
                    );
                    position = 0;
                }
            }
        }
        Sleep(10);
    }
    return 0;
}

BOOL APIENTRY DllMain(
    HMODULE module,
    DWORD reason,
    LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module);
        CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
    }
    return TRUE;
}
