#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

int chessZoomRate;
int chessBoardX, chessBoardY;

int nbw = 1;

struct Color *colors;

wchar_t *outputFormatPrefix = L"\x1b[38;2;%d;%d;%dm"; // 输出格式前缀

wchar_t lt = L'╔', rt = L'╗', lb = L'╚', rb = L'╝', h = L'═', v = L'║', t = L'╦', b = L'╩', l = L'╠', r = L'╣', m = L'╬'; // 棋盘制表符

COORD bufferSize; // 缓冲区大小

struct Color
{
    int r;
    int g;
    int b;
};

struct Color start = {0xfc, 0x35, 0x4c}, end = {0xa, 0xbf, 0xbc}, defaultColor = {200, 200, 200}; // 渐变色起始颜色，结束颜色，输出默认颜色

struct Color *CreateColorArray(int length) // 创建渐变色数组
{
    return (struct Color *)calloc(length, sizeof(struct Color));
}

void GetGrandientColorArray(struct Color *colors, int length) // 获取渐变色数组
{
    int deltar = end.r - start.r, deltag = end.g - start.g, deltab = end.b - start.b;
    float rate = 1.0 / ((length - 1) * 1.0);
    for (int i = 0; i < length; i++)
    {
        colors[i].r = start.r + deltar * rate * i;
        colors[i].g = start.g + deltag * rate * i;
        colors[i].b = start.b + deltab * rate * i;
    }
}

DWORD Initialize_Console() // 初始化控制台，设置编码为UTF-8，设置标题，设置输出颜色
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))
        return GetLastError();
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE; // 移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;     // 移除插入模式
    // mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, mode);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(hOut, &CursorInfo); // 获取控制台光标信息
    CursorInfo.bVisible = false;             // 隐藏控制台光标
    SetConsoleCursorInfo(hOut, &CursorInfo); // 设置控制台光标状态
    _wsetlocale(LC_ALL, L"zh_CN.UTF-8");
    SetConsoleTitleA("HEU Gobang Platform");
}

void Console_Print(wchar_t *str, struct Color color) // 输出彩色字符串
{
    wprintf(outputFormatPrefix, color.r, color.g, color.b);
    DWORD ws;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str, wcslen(str), &ws, NULL);
}

void Console_Print_Prefix(wchar_t *str, struct Color color, int x, int y) // x,y为字符串左上角坐标
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
    Console_Print(str, color);
}

void DrawChess(int x, int y, int bw)
{
    if (chessZoomRate != 1)
    {
        wchar_t *chess = (bw == 2 ? L" ⚪" : L" ⚫");
        Console_Print_Prefix(chess, colors[y - chessBoardY], x - 1, y);
    }
    else
    {
        wchar_t *chess = (bw == 2 ? L"⚪" : L"⚫");
        Console_Print_Prefix(chess, colors[y - chessBoardY], x, y);
    }
}

void DrawChessBoard(int x, int y, int x1, int y1, int **board) // x,y,x1,y1为棋盘可绘制矩形区域，自动在此区域内居中绘制棋盘
{
    int zoomRate = 1; // 缩放倍率
    while (zoomRate * 28 < (x1 - x) && zoomRate * 14 < (y1 - y))
        zoomRate++;
    zoomRate--;
    x += (x1 - x - zoomRate * 28) / 2 + 1;
    y += (y1 - y - zoomRate * 14) / 2 + 1;
    chessZoomRate = zoomRate;
    chessBoardX = x;
    chessBoardY = y;
    colors = CreateColorArray(28 * zoomRate);
    GetGrandientColorArray(colors, 14 * zoomRate);
    wchar_t *boardtop = (wchar_t *)calloc(28 * zoomRate + 1, sizeof(wchar_t));
    for (int i = 0; i < 28 * zoomRate; i++)
    {
        if (i % (2 * zoomRate) == 0)
            boardtop[i] = t;
        else
            boardtop[i] = h;
    }
    boardtop[0] = lt;
    boardtop[28 * zoomRate] = rt;
    wchar_t *boardbuttom = (wchar_t *)calloc(28 * zoomRate + 1, sizeof(wchar_t));
    for (int i = 0; i < 28 * zoomRate; i++)
    {
        if (i % (2 * zoomRate) == 0)
            boardbuttom[i] = b;
        else
            boardbuttom[i] = h;
    }
    boardbuttom[0] = lb;
    boardbuttom[28 * zoomRate] = rb;
    wchar_t *boardline = (wchar_t *)calloc(28 * zoomRate + 1, sizeof(wchar_t));
    for (int i = 0; i < 28 * zoomRate; i++)
    {
        if (i % (2 * zoomRate) == 0)
            boardline[i] = m;
        else
            boardline[i] = h;
    }
    boardline[0] = l;
    boardline[28 * zoomRate] = r;
    wchar_t *boardmid = (wchar_t *)calloc(28 * zoomRate + 1, sizeof(wchar_t));
    for (int i = 0; i < 28 * zoomRate; i++)
    {
        if (i % (2 * zoomRate) == 0)
            boardmid[i] = v;
        else
            boardmid[i] = L' ';
    }
    boardmid[28 * zoomRate] = v;
    Console_Print_Prefix(boardtop, colors[0], x, y);
    for (int i = 1; i < zoomRate; i++)
    {
        Console_Print_Prefix(boardmid, colors[i], x, y + i);
    }
    for (int i = 1; i < 13; i++)
    {
        Console_Print_Prefix(boardline, colors[i * zoomRate], x, y + (i * zoomRate));
        for (int j = 1; j < zoomRate; j++)
        {
            Console_Print_Prefix(boardmid, colors[i * zoomRate + j], x, y + (i * zoomRate) + j);
        }
    }
    Console_Print_Prefix(boardbuttom, colors[13 * zoomRate], x, y + (13 * zoomRate));
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (board[i][j] != 0)
            {
                DrawChess(x + (j)*2 * zoomRate, y + (i)*zoomRate, board[i][j]);
            }
        }
    }
}

void full_screen() // 全屏显示控制台窗口
{
    HWND hwnd = GetConsoleWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER); // 设置窗口样式
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);                                                                     // 设置窗口位置和大小
    HANDLE Hand;
    CONSOLE_SCREEN_BUFFER_INFO Info;
    Hand = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(Hand, &Info);
    SMALL_RECT rect = Info.srWindow;
    COORD size = {rect.Right + 1, rect.Bottom + 1}; // 定义缓冲区大小，保持缓冲区大小和屏幕大小一致即可取消边框
    SetConsoleScreenBufferSize(Hand, size);
    bufferSize = size;
}
// 将光标转换为棋盘坐标
void GetChessBoardPos(int *x, int *y)
{
    *x = (*x - chessBoardX) / chessZoomRate / 2;
    *y = (*y - chessBoardY) / chessZoomRate;
}

void GetMouseInput()
{
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);

    COORD coordScreen;
    coordScreen = inRec.Event.MouseEvent.dwMousePosition;
    int x = coordScreen.X;
    int y = coordScreen.Y;
    GetChessBoardPos(&x, &y);
    if (x >= 0 && x < 15 && y >= 0 && y < 15)
    {
        DrawChess(chessBoardX + (x)*2 * chessZoomRate, chessBoardY + (y)*chessZoomRate, nbw);
        nbw = nbw == 1 ? 2 : 1;
    }
}

int main()
{
    Initialize_Console();
    full_screen();
    Console_Print(L"Welcome to HEU Gobang Platform!\n", defaultColor);
    // DrawChessBoard((bufferSize.X - 30) * 0.7, (bufferSize.Y - 15) / 2, NULL);
    int **board = (int **)calloc(sizeof(int *), 15);
    for (int i = 0; i < 15; i++)
    {
        board[i] = (int *)calloc(sizeof(int), 15);
        ;
    }
    board[0][0] = 1;
    board[0][1] = 2;
    board[1][0] = 2;
    board[1][1] = 1;
    DrawChessBoard(0, 0, bufferSize.X, bufferSize.Y, board);
    while (1)
        GetMouseInput();

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){bufferSize.X - 1, bufferSize.Y - 1});
    system("pause");
}