#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>

//export function in gui.c
DWORD Initialize_Console();
void ReadNameFile();
void MapColorTable();
void full_screen();
void ClearScreen();
void Print_Logo();

