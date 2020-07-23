#include <launcher/main.h>

#include <windows.h>

#include <cstdlib>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return tg::Main(__argc, __argv);
}
