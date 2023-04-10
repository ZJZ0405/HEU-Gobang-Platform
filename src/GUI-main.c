#include "ConsoleGUI/gui.h"

int main()
{
    Initialize_Console();
    ReadNameFile();
    MapColorTable();
    full_screen();
    ClearScreen();
    player1 = (wchar_t *)malloc(sizeof(wchar_t) * 20);
    player2 = (wchar_t *)malloc(sizeof(wchar_t) * 20);
    Print_Logo();
}
