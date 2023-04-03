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

#pragma execution_character_set("utf-8")

const wchar_t logo[25][51] = {L"                      +3666!.                     ", L"               v66  1666666668o  66-              ", L"           .3v.66oi666666o 666666666 38           ", L"        .6zv66666-6666666;636668.n36666 68        ", L"      .6 866666686.8868 666666v.3-u666666%;6      ", L"     3z866i..n666i66866666666666.16666666 6v6+    ", L"    6 66666v*666663!^33~~o~o86.8666.6!.-66668 6   ", L"   6.66 66666666.6~~;;*******;;~;63666z6666666 8  ", L"  6 6666 ; i66.8~;**^^+++++++^^*;;~866666 8  .6 6 ", L" 3 6666n 8866zo;**^+-.      -.-+^*;~o.638. i6666~+", L" 6!666688666*~;*^+-. noooooooz..-+^*~~ 666666666 6", L"~o6666666661!;*^-.  #--....--.3  .+^*;68666666@883", L"6 6+n~    +oo-...+o~.#i6^&$8 .n*....~n-. --o~..#6n", L"6 6v#!..- ;&%+...~#6-#i.......#i.- .!#o ..~#3- #6v", L"^o6         .       ..8&3..~+ .                #86", L" 6z66666n666.o;*^+-.           .-+^;~z-666666666 6", L" ! 666;38-666.~~;*^+-# ;#.# -#-+^*;~1 666a666666u-", L"  6 666!-6.666i6~;;*^^++++++^^^*;;o666663.68666 6 ", L"   6 66666.6866636o~~;;*****;;~~1v8666o83; 666 6  ", L"    6 36668v66666666 363ava66a-6666666z666666 6   ", L"     a6i66666. 666666666666666666in.u8!6666.6.    ", L"      .8^6666836668638 8u1i36!6z631nu6666*!8      ", L"         86 366668.*-16i8z!..o186666666 81        ", L"            68 86666666666666666666! 66           ", L"                66~  u6666666v  u66               "};

int chessZoomRate;
int chessBoardX, chessBoardY, battlePanelX, battlePanelY;
int surrenderX, surrenderY, surrenderWidth, surrenderHeight;
// 是否可以悔棋
bool canRegret = false;

// 添加悔棋功能的全局变量
int regretX, regretY, regretWidth, regretHeight;
// 上一步棋的全局变量
int lastX = -1, lastY = -1;

wchar_t *player1;
wchar_t *player2;

int nbw = 1;

struct Color *colors;

wchar_t *outputFormatPrefix = L"\x1b[38;2;%d;%d;%dm"; // 输出格式前缀

wchar_t lt = L'┏', rt = L'┓', lb = L'┗', rb = L'┛', h = L'━', v = L'┃', t = L'┳', b = L'┻', l = L'┣', r = L'┫', m = L'╋'; // 棋盘制表符

COORD bufferSize; // 缓冲区大小

void Game_Start();

void Regret(int **board);

void Print_Logo();

void Print_Grandient_Logo();

struct Color
{
    int r;
    int g;
    int b;
};

struct Color start = {238, 121, 89}, end = {177, 213, 200}, defaultColor = {255, 238, 111}; // 渐变色起始颜色，结束颜色，输出默认颜色
/**
 * @brief Create a Color Array object
 *
 * @param length
 * @return struct Color*
 */
struct Color *CreateColorArray(int length) // 创建渐变色数组
{
    return (struct Color *)calloc(length, sizeof(struct Color));
}
/**
 * @brief Get the Clear Color Array object
 *
 * @param colors
 * @param length
 */
void GetClearColorArray(struct Color *colors, int length)
{
    for (int i = 0; i < length; i++)
    {
        colors[i].r = 219;
        colors[i].g = 133;
        colors[i].b = 64;
    }
}
/**
 * @brief Get the Grandient Color Array object
 *
 * @param colors
 * @param length
 */
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
/**
 * @brief 初始化控制台
 *
 * @return DWORD GetLastError返回值
 */
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
    //_wsetlocale(LC_ALL, L"zh_CN.UTF-8");
    _wsetlocale(LC_ALL, L"");
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleTitleA("HEU Gobang Platform");
    // SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
}
/**
 * @brief 输出彩色字符串
 *
 * @param str
 * @param color
 */
void Console_Print(wchar_t *str, struct Color color) // 输出彩色字符串
{
    wprintf(outputFormatPrefix, color.r, color.g, color.b);
    DWORD ws;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str, wcslen(str), &ws, NULL);
}
/**
 * @brief 输出彩色字符串，带坐标
 *
 * @param str
 * @param color
 * @param x
 * @param y
 */
void Console_Print_Prefix(wchar_t *str, struct Color color, int x, int y) // x,y为字符串左上角坐标
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
    Console_Print(str, color);
}
/**
 * @brief 画棋子
 *
 * @param x
 * @param y
 * @param bw
 */
void DrawChess(int x, int y, int bw)
{
    wchar_t *chess = L"●";
    Console_Print_Prefix(chess, bw == 2 ? (struct Color){255, 255, 255} /*colors[y - chessBoardY]*/ : (struct Color){30, 30, 30}, x, y);
}
/**
 * @brief 画棋盘
 *
 * @param x
 * @param y
 * @param x1
 * @param y1
 * @param board
 */
void DrawChessBoard(int x, int y, int x1, int y1, int **board) // x,y,x1,y1为棋盘可绘制矩形区域，自动在此区域内居中绘制棋盘
{
    int zoomRate = 1; // 缩放倍率
    while (zoomRate * 28 < (x1 - x) && zoomRate * 15 < (y1 - y))
        zoomRate++;
    zoomRate--;
    x += (x1 - x - zoomRate * 28) / 2 + 1;
    y += (y1 - y - zoomRate * 15) / 2 + 1;
    chessZoomRate = zoomRate;
    chessBoardX = x;
    chessBoardY = y;
    colors = CreateColorArray(30 * zoomRate);
    GetGrandientColorArray(colors, 15 * zoomRate);
    // GetClearColorArray(colors, 15 * zoomRate);
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
    for (int i = 1; i < 14; i++)
    {
        Console_Print_Prefix(boardline, colors[i * zoomRate], x, y + (i * zoomRate));
        for (int j = 1; j < zoomRate; j++)
        {
            Console_Print_Prefix(boardmid, colors[i * zoomRate + j], x, y + (i * zoomRate) + j);
        }
    }
    Console_Print_Prefix(boardbuttom, colors[14 * zoomRate], x, y + (14 * zoomRate));
    for (int i = 14; i > -1; i--)
    {
        for (int j = 14; j > -1; j--)
        {
            if (board[i][j] != 0)
            {
                DrawChess(x + (j)*2 * zoomRate, y + (i)*zoomRate, board[i][j]);
            }
        }
    }
}

void UpdateChessBoard(int **newboard, int newX, int newY)
{
    // 画所有棋子
    for (int i = 14; i > -1; i--)
    {
        for (int j = 14; j > -1; j--)
        {
            if (!((i == lastY || j == lastX) || (i == newY || j == newX)))
                continue;
            if (newboard[i][j] != 0)
            {
                DrawChess(chessBoardX + (j)*2 * chessZoomRate, chessBoardY + (i)*chessZoomRate, newboard[i][j]);
            }
        }
    }
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    DrawChess(chessBoardX + (newX)*2 * chessZoomRate, chessBoardY + (newY)*chessZoomRate, newboard[newY][newX]);
    SetConsoleTextAttribute(hOut, 0x0000);
}
/**
 * @brief 全屏显示控制台窗口
 *
 */
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
/**
 * @brief Get the Chess Board Pos object
 *
 * @param x
 * @param y
 */
void GetChessBoardPos(int *x, int *y)
{
    *x = (*x - chessBoardX) / chessZoomRate / 2;
    *y = (*y - chessBoardY) / chessZoomRate;
}
/**
 * @brief 判断是否有一方胜利
 *
 * @param board
 * @return true
 * @return false
 */
bool CheckWin(int **board)
{ // 判断是否有一方胜利
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4])
            {
                return true;
            }
        }
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j] && board[i][j] == board[i + 4][j])
            {
                return true;
            }
        }
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3] && board[i][j] == board[i + 4][j + 4])
            {
                return true;
            }
        }
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 4; j < 15; j++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3] && board[i][j] == board[i + 4][j - 4])
            {
                return true;
            }
        }
    }
    return false;
}
/**
 * @brief 清空屏幕
 *
 */
void ClearScreen()
{
    wchar_t *clear = (wchar_t *)malloc(sizeof(wchar_t) * bufferSize.X);
    for (int i = 0; i < bufferSize.X; i++)
    {
        clear[i] = L' ';
    }
    for (int j = 0; j < bufferSize.Y; j++)
    {
        Console_Print_Prefix(clear, (struct Color){0, 0, 0}, 0, j);
    }
}
/**
 * @brief 绘制对战信息区域
 *
 * @param highLightPlayer
 */
void DrawBattlePanel(int highLightPlayer)
{ // 在左侧生成一个带边框的窗口，显示玩家信息,边框使用lt,bt等字符，边框使用defaultColor，文字使用纯白
    int x = 0, y = 0;
    battlePanelX = x;
    battlePanelY = y;
    int width = bufferSize.X * 0.25, height = bufferSize.Y;
    Console_Print_Prefix(L"╔", defaultColor, x, y);
    for (int i = 0; i < width - 2; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, x + 1 + i, y);
    }
    Console_Print_Prefix(L"╗", defaultColor, x + width - 1, y);
    for (int i = 0; i < height - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x, y + 1 + i);
    }
    Console_Print_Prefix(L"╚", defaultColor, x, y + height - 1);
    for (int i = 0; i < width - 2; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, x + 1 + i, y + height - 1);
    }
    Console_Print_Prefix(L"╝", defaultColor, x + width - 1, y + height - 1);
    for (int i = 0; i < height - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x + width - 1, y + 1 + i);
    }
    Console_Print_Prefix(L"白子玩家", defaultColor, x + 2, y + 1);
    Console_Print_Prefix(L"黑子玩家", defaultColor, x + 2, y + 4);
    Console_Print_Prefix(player1, highLightPlayer == 1 ? (struct Color){240, 200, 183} : defaultColor, x + 2, y + 2);
    Console_Print_Prefix(player2, highLightPlayer == 2 ? (struct Color){240, 200, 183} : defaultColor, x + 2, y + 5);
    // 绘制认输与悔棋按钮，位于玩家信息窗口内，按钮至少三格高，十二格宽，水平居中，按钮内文字也水平居中
    int buttonWidth = 12, buttonHeight = 3;
    int buttonX = (width - buttonWidth) / 2 + x, buttonY = (height - buttonHeight) / 2 + y;
    Console_Print_Prefix(L"╔", defaultColor, buttonX, buttonY);
    for (int i = 0; i < buttonWidth - 2; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, buttonX + 1 + i, buttonY);
    }
    Console_Print_Prefix(L"╗", defaultColor, buttonX + buttonWidth - 1, buttonY);
    for (int i = 0; i < buttonHeight - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, buttonX, buttonY + 1 + i);
    }
    Console_Print_Prefix(L"╚", defaultColor, buttonX, buttonY + buttonHeight - 1);
    for (int i = 0; i < buttonWidth - 2; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, buttonX + 1 + i, buttonY + buttonHeight - 1);
    }
    Console_Print_Prefix(L"╝", defaultColor, buttonX + buttonWidth - 1, buttonY + buttonHeight - 1);
    for (int i = 0; i < buttonHeight - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, buttonX + buttonWidth - 1, buttonY + 1 + i);
    }
    Console_Print_Prefix(L"认 输", defaultColor, buttonX + (buttonWidth - 4) / 2, buttonY + (buttonHeight - 1) / 2);
    // 认输按钮写入全局变量surrenderX
    surrenderX = buttonX;
    surrenderY = buttonY;
    // 写入surrenderWidth
    surrenderWidth = buttonWidth;
    // 写入surrenderHeight
    surrenderHeight = buttonHeight;
    buttonY += buttonHeight + 1;
    Console_Print_Prefix(L"╔", defaultColor, buttonX, buttonY);
    for (int i = 0; i < buttonWidth - 2; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, buttonX + 1 + i, buttonY);
    }
    Console_Print_Prefix(L"╗", defaultColor, buttonX + buttonWidth - 1, buttonY);
    for (int i = 0; i < buttonHeight - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, buttonX, buttonY + 1 + i);
    }
    Console_Print_Prefix(L"╚", defaultColor, buttonX, buttonY + buttonHeight - 1);
    for (int i = 0; i < buttonWidth - 2; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, buttonX + 1 + i, buttonY + buttonHeight - 1);
    }
    Console_Print_Prefix(L"╝", defaultColor, buttonX + buttonWidth - 1, buttonY + buttonHeight - 1);
    for (int i = 0; i < buttonHeight - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, buttonX + buttonWidth - 1, buttonY + 1 + i);
    }
    Console_Print_Prefix(L"悔 棋", defaultColor, buttonX + (buttonWidth - 4) / 2, buttonY + (buttonHeight - 1) / 2);
    // 悔棋按钮写入全局变量regretX
    regretX = buttonX;
    regretY = buttonY;
    // 写入regretWidth
    regretWidth = buttonWidth;
    // 写入regretHeight
    regretHeight = buttonHeight;
}

void UpdateBattlePanel(int highLightPlayer)
{
    Console_Print_Prefix(player1, highLightPlayer == 1 ? (struct Color){240, 200, 183} : defaultColor, battlePanelX + 2, battlePanelY + 2);
    Console_Print_Prefix(player2, highLightPlayer == 2 ? (struct Color){240, 200, 183} : defaultColor, battlePanelX + 2, battlePanelY + 5);
}
/**
 * @brief 绘制标题
 *
 */
void DrawBoardLine()
{ // 为整个控制台绘制边框，没有保留边界
    int x = 0, y = 0;
    int width = bufferSize.X, height = bufferSize.Y;
    // 先生成字符串数组 再打印
    wchar_t *top = (wchar_t *)malloc(sizeof(wchar_t) * (width + 1));
    wchar_t *bottom = (wchar_t *)malloc(sizeof(wchar_t) * (width + 1));
    for (int i = 0; i < width; i++)
    {
        top[i] = L'═';
        bottom[i] = L'═';
    }
    top[width] = L'\0';
    bottom[width] = L'\0';
    Console_Print_Prefix(top, defaultColor, x, y);
    Console_Print_Prefix(bottom, defaultColor, x, y + height - 1);
    free(top);
    free(bottom);
    Console_Print_Prefix(L"╔", defaultColor, x, y);
    Console_Print_Prefix(L"╗", defaultColor, x + width - 1, y);
    for (int i = 0; i < height - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x, y + 1 + i);
    }
    Console_Print_Prefix(L"╚", defaultColor, x, y + height - 1);
    Console_Print_Prefix(L"╝", defaultColor, x + width - 1, y + height - 1);
    for (int i = 0; i < height - 2; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x + width - 1, y + 1 + i);
    }
    // 添加窗口标题栏，标题为HEU Gobang Platform
    Console_Print_Prefix(L"HEU Gobang Platform", defaultColor, x + (width - 20) / 2, y);
}
/**
 * @brief 绘制胜利对话框
 *
 * @param bw
 */
void DrawWinnerDialog(int bw)
{
    // 在屏幕中心30%位置绘制对话框
    int x = bufferSize.X / 2 - 20;
    int y = bufferSize.Y / 2 - 5;
    int width = 40;
    int height = 10;
    // 绘制胜方提示
    wchar_t *winner;
    // 填充对话框为黑色
    // 生成背景填充字符串数组
    wchar_t *fill = (wchar_t *)malloc(sizeof(wchar_t) * (width + 1));
    for (int i = 0; i < width + 1; i++)
    {
        fill[i] = L' ';
    }
    for (int j = 0; j < height; j++)
    {
        Console_Print_Prefix(fill, (struct Color){0, 0, 0}, x, y + j);
    }
    if (bw == 1)
    {
        winner = L"黑方胜利";
    }
    else
    {
        winner = L"白方胜利";
    }
    Console_Print_Prefix(winner, defaultColor, x + width / 2 - 4, y + height / 2 - 1);
    // 绘制对话框
    Console_Print_Prefix(L"╔", defaultColor, x, y);
    Console_Print_Prefix(L"╗", defaultColor, x + width - 1, y);
    Console_Print_Prefix(L"╚", defaultColor, x, y + height - 1);
    Console_Print_Prefix(L"╝", defaultColor, x + width - 1, y + height - 1);
    for (int i = 1; i < width - 1; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, x + i, y);
        Console_Print_Prefix(L"═", defaultColor, x + i, y + height - 1);
    }
    for (int i = 1; i < height - 1; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x, y + i);
        Console_Print_Prefix(L"║", defaultColor, x + width - 1, y + i);
    }
    // 绘制按钮
    Console_Print_Prefix(L"重新开始", defaultColor, x + width / 2 - 4, y + height - 2);
    Console_Print_Prefix(L"退出游戏", defaultColor, x + width / 2 - 4, y + height - 1);
    // 绘制光标
    Console_Print_Prefix(L"▶", defaultColor, x + width / 2 - 6, y + height - 2);
    // 获取鼠标输入
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
LABEL1:
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);
    COORD coordScreen;
    coordScreen = inRec.Event.MouseEvent.dwMousePosition;
    int x1 = coordScreen.X;
    int y1 = coordScreen.Y;
    if (x1 >= x + width / 2 - 4 && x1 <= x + width / 2 + 4 && y1 == y + height - 2)
    {
        // 回收内存
        free(fill);
        // 重新开始
        ClearScreen();
        Print_Logo();
    }
    else if (x1 >= x + width / 2 - 4 && x1 <= x + width / 2 + 4 && y1 == y + height - 1)
    {
        // 退出游戏
        exit(0);
    }
    else
    {
        // 重新获取鼠标输入
        goto LABEL1;
    }
}
/**
 * @brief 绘制认输确认对话框
 *
 * @return true
 * @return false
 */
bool DrawSurrenderConfirmDialog()
{
    // 绘制确认认输对话框
    int x = bufferSize.X / 2 - 20;
    int y = bufferSize.Y / 2 - 5;
    int width = 40;
    int height = 10;
    // 填充对话框为黑色
    wchar_t *fill = (wchar_t *)malloc(sizeof(wchar_t) * (width + 1));
    for (int i = 0; i < width + 1; i++)
    {
        fill[i] = L' ';
    }
    for (int j = 0; j < height; j++)
    {
        Console_Print_Prefix(fill, (struct Color){0, 0, 0}, x, y + j);
    }
    // 绘制对话框
    Console_Print_Prefix(L"╔", defaultColor, x, y);
    Console_Print_Prefix(L"╗", defaultColor, x + width - 1, y);
    Console_Print_Prefix(L"╚", defaultColor, x, y + height - 1);
    Console_Print_Prefix(L"╝", defaultColor, x + width - 1, y + height - 1);
    for (int i = 1; i < width - 1; i++)
    {
        Console_Print_Prefix(L"═", defaultColor, x + i, y);
        Console_Print_Prefix(L"═", defaultColor, x + i, y + height - 1);
    }
    for (int i = 1; i < height - 1; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x, y + i);
        Console_Print_Prefix(L"║", defaultColor, x + width - 1, y + i);
    }
    // 绘制提示
    Console_Print_Prefix(L"是否认输？", defaultColor, x + width / 2 - 4, y + height / 2 - 1);
    // 绘制按钮
    Console_Print_Prefix(L"是", defaultColor, x + width / 2 - 4, y + height - 2);
    Console_Print_Prefix(L"否", defaultColor, x + width / 2 + 2, y + height - 2);
    // 绘制光标
    Console_Print_Prefix(L"▶", defaultColor, x + width / 2 - 6, y + height - 2);
    // 获取鼠标输入
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
LABEL1:
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);
    COORD coordScreen;
    coordScreen = inRec.Event.MouseEvent.dwMousePosition;
    int x1 = coordScreen.X;
    int y1 = coordScreen.Y;
    if (x1 >= x + width / 2 - 4 && x1 <= x + width / 2 - 2 && y1 == y + height - 2)
    {
        return true;
    }
    else if (x1 >= x + width / 2 + 2 && x1 <= x + width / 2 + 4 && y1 == y + height - 2)
    {
        // 取消认输
        return false;
    }
    else
    {
        // 重新获取鼠标输入
        goto LABEL1;
    }
}
/**
 * @brief Get the Mouse Input object.Global Input Process Function
 *
 * @param board
 * @param stopflag
 */
void GetMouseInput(int **board, bool *stopflag)
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
    // 添加认输响应事件，判断鼠标输入是否在认输按钮区域
    if (x >= surrenderX && x <= surrenderX + 8 && y >= surrenderY && y <= surrenderY + 1)
    {
        if (DrawSurrenderConfirmDialog())
        {
            *stopflag = true;
            DrawWinnerDialog(nbw == 1 ? 2 : 1);
        }
        else
        {
            ClearScreen();
            DrawBoardLine();
            DrawChessBoard(bufferSize.X * 0.25, 0, bufferSize.X, bufferSize.Y, board);
            DrawBattlePanel(nbw);
        }

        return;
    }
    // 添加悔棋响应事件，判断鼠标输入是否在悔棋按钮区域
    if (x >= regretX && x <= regretX + 8 && y >= regretY && y <= regretY + 1)
    {
        // 悔棋
        Regret(board);
        return;
    }
    GetChessBoardPos(&x, &y);
    if (x >= 0 && x < 15 && y >= 0 && y < 15)
    {
        if (board[y][x] != 0)
            return;
        board[y][x] = nbw;
        canRegret = true;
        /*    for (int i = 0; i < 15; i++)
           {
               for (int j = 0; j < 15; j++)
               {
                   if (board[i][j] != 0)
                   {
                       DrawChess(chessBoardX + (j)*2 * chessZoomRate, chessBoardY + (i)*chessZoomRate, board[i][j]);
                   }
               }
           } */
        UpdateChessBoard(board, x, y);
        lastX = x;
        lastY = y;
        if (CheckWin(board))
        {
            *stopflag = true;
            DrawWinnerDialog(nbw);
        }
        nbw = nbw == 1 ? 2 : 1;
        // 让正在下棋的一方的名字高亮显示，即将下棋的一方的名字变为红色
        UpdateBattlePanel(nbw);
    }
}
/**
 * @brief 绘制对话框
 *
 * @param x
 * @param y
 * @param width
 * @param height
 */
void DrawDialog(int x, int y, int width, int height)
{
    // 绘制对话框
    Console_Print_Prefix(L"╔", defaultColor, x, y);
    Console_Print_Prefix(L"╗", defaultColor, x + width - 1, y);
    Console_Print_Prefix(L"╚", defaultColor, x, y + height - 1);
    Console_Print_Prefix(L"╝", defaultColor, x + width - 1, y + height - 1);
    for (int i = 1; i < width - 1; i++)
    {
        // 先生成字符串再打印
        wchar_t *str = (wchar_t *)calloc(sizeof(wchar_t), width);
        for (int j = 1; j < width - 1; j++)
        {
            str[j - 1] = L'═';
        }
        Console_Print_Prefix(str, defaultColor, x + 1, y);
        Console_Print_Prefix(str, defaultColor, x + 1, y + height - 1);
    }

    for (int i = 1; i < height - 1; i++)
    {
        Console_Print_Prefix(L"║", defaultColor, x, y + i);
        Console_Print_Prefix(L"║", defaultColor, x + width - 1, y + i);
    }
    // 用黑色填充
    for (int i = 1; i < height - 1; i++)
    {
        wchar_t *str = (wchar_t *)calloc(sizeof(wchar_t), width);
        for (int j = 1; j < width - 1; j++)
        {
            str[j - 1] = L' ';
        }
        Console_Print_Prefix(str, defaultColor, x + 1, y + i);
    }
}
/**
 * @brief 悔棋
 *
 * @param board
 */
void Regret(int **board)
{
    if (canRegret)
    {
        board[lastY][lastX] = 0;
        nbw = nbw == 1 ? 2 : 1;
        DrawChessBoard(bufferSize.X * 0.25, 0, bufferSize.X, bufferSize.Y, board);
        DrawBattlePanel(nbw);
        canRegret = false;
    }
}
/**
 * @brief Get the First Player object
 *
 * @return int
 */
int GetFirst()
{
    // 绘制一个对话框，询问谁先手，返回bw值
    int bw = 1;
    int x = bufferSize.X * 0.25;
    int y = bufferSize.Y * 0.25;
    int width = bufferSize.X * 0.5;
    int height = bufferSize.Y * 0.5;
    char tplayer1[20];
    char tplayer2[20];
    DrawDialog(x, y, width, height);
    wcstombs(tplayer1, player1, 20);
    wcstombs(tplayer2, player2, 20);
    Console_Print_Prefix(L"请选择先手方：", defaultColor, x + width / 2 - 6, y + height / 2 - 2);
    Console_Print_Prefix(player1, defaultColor, x + (width - strlen(tplayer1)) / 2, y + height / 2 - 1);
    Console_Print_Prefix(player2, defaultColor, x + (width - strlen(tplayer2)) / 2, y + height / 2);
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
LABEL1:
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);
    COORD coordScreen;
    coordScreen = inRec.Event.MouseEvent.dwMousePosition;
    int x1 = coordScreen.X;
    int y1 = coordScreen.Y;
    if (x1 >= x + width / 2 - 4 && x1 <= x + width / 2 + 4 && y1 == y + height / 2 - 1)
    {
        // 黑子
        bw = 1;
    }
    else if (x1 >= x + width / 2 - 4 && x1 <= x + width / 2 + 4 && y1 == y + height / 2)
    {
        // 白子
        bw = 2;
    }
    else
    {
        // 重新获取鼠标输入
        goto LABEL1;
    }
    return bw;
}
/**
 * @brief 游戏开始
 *
 */
void Game_Start()
{
    ClearScreen();
    lastX = -1;
    lastY = -1;
    // Console_Print(L"Welcome to HEU Gobang Platform!\n", defaultColor);
    int **board = (int **)calloc(sizeof(int *), 15);
    for (int i = 0; i < 15; i++)
    {
        board[i] = (int *)calloc(sizeof(int), 15);
    }
    DrawBoardLine();
    nbw = GetFirst();
    ClearScreen();
    DrawBoardLine();
    DrawChessBoard(bufferSize.X * 0.25, 0, bufferSize.X, bufferSize.Y, board);
    DrawBattlePanel(nbw);
    bool stopflag = false;
    while (!stopflag)
    {
        GetMouseInput(board, &stopflag);
    }
}

void GetPlayerName(wchar_t *player)
{
    // 绘制一个输入框，提示输入玩家名字
    int x = bufferSize.X * 0.25;
    int y = bufferSize.Y * 0.25;
    int width = bufferSize.X * 0.5;
    int height = bufferSize.Y * 0.5;
    DrawDialog(x, y, width, height);
    Console_Print_Prefix(L"请输入玩家", defaultColor, x + width / 2 - 6, y + height / 2 - 2);
    // 打印下划线
    for (int i = 0; i < 20; i++)
    {
        Console_Print_Prefix(L"_", defaultColor, x + width / 2 - 10 + i, y + height / 2 - 1);
    }
    // 将光标移动到输入框中
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x + width / 2 - 10;
    coord.Y = y + height / 2 - 1;
    SetConsoleCursorPosition(hOut, coord);
    // 接收玩家输入的名字
    wscanf(L"%ls", player);
    // 将玩家输入的名字赋值给player
}

wchar_t **firstname;
wchar_t **lastname;
int firstcount, lastcount;

void ReadNameFile()
{
    firstname = (wchar_t **)malloc(sizeof(wchar_t *) * 2000);
    lastname = (wchar_t **)malloc(sizeof(wchar_t *) * 2000);
    // 读取first.names，以utf-8文本模式打开并分行写入firstname数组
    FILE *fp;
    fp = fopen("first.names", "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    int i = 0;
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        firstname[i] = (wchar_t *)malloc(sizeof(wchar_t) * 100);
        mbstowcs(firstname[i], line, 100);
        i++;
    }
    firstcount = i;
    fclose(fp);
    // 读取last.names，以utf-8文本模式打开并分行写入lastname数组
    fp = fopen("last.names", "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    i = 0;
    while (fgets(line, 100, fp) != NULL)
    {
        lastname[i] = (wchar_t *)malloc(sizeof(wchar_t) * 100);
        mbstowcs(lastname[i], line, 100);
        i++;
    }
    lastcount = i;
    fclose(fp);
}

void Print_Logo()
{
    DrawBoardLine();
    for (int i = 0; i < 25; i++)
    {
        Console_Print_Prefix(logo[i], (struct Color){255, 255, 255}, bufferSize.X * 0.1, (bufferSize.Y - 24) / 2 + i);
    }
    // Print_Grandient_Logo();
    Console_Print_Prefix(L"Welcome to HEU Gobang Platform!", defaultColor, 54 + (bufferSize.X - 54 - 30) / 2, bufferSize.Y / 2 - 8);
    // Console_Print_Prefix(L"点击左键继续", defaultColor, 54 + (bufferSize.X - 54 - 12) / 2, bufferSize.Y / 2 + 2);
    // 在欢迎语下方分别绘制热座模式、人机对战、退出游戏三个按钮，使用制表符分别绘制边框。位于玩家信息窗口内，每个按钮至少三格高，十二格宽，与欢迎语中心对齐，按钮内文字也水平居中
    Console_Print_Prefix(L"热座模式", defaultColor, 54 + (bufferSize.X - 54 - 8) / 2, bufferSize.Y / 2);
    Console_Print_Prefix(L"人机对战", defaultColor, 54 + (bufferSize.X - 54 - 8) / 2, bufferSize.Y / 2 + 4);
    Console_Print_Prefix(L"退出游戏", defaultColor, 54 + (bufferSize.X - 54 - 8) / 2, bufferSize.Y / 2 + 8);
    // 等待鼠标点击
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
LABEL1:
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);
    COORD coordScreen;
    coordScreen = inRec.Event.MouseEvent.dwMousePosition;
    int x1 = coordScreen.X;
    int y1 = coordScreen.Y;
    if (x1 >= 54 + (bufferSize.X - 54 - 12) / 2 && x1 <= 54 + (bufferSize.X - 54 - 12) / 2 + 12 && y1 == bufferSize.Y / 2)
    {
        ClearScreen();
        DrawBoardLine();
        GetPlayerName(player1);
        GetPlayerName(player2);
        // 热座模式
        Game_Start();
        // 输入玩家信息
    }
    else if (x1 >= 54 + (bufferSize.X - 54 - 12) / 2 && x1 <= 54 + (bufferSize.X - 54 - 12) / 2 + 12 && y1 == bufferSize.Y / 2 + 4)
    {
        ClearScreen();
        DrawBoardLine();
        GetPlayerName(player1);
        // 随机生成人名
        srand((unsigned)time(NULL));
        int first = rand() % firstcount;
        int last = rand() % lastcount;
        wcscpy(player2, firstname[first]);
        wcscat(player2, lastname[last]);
        // 遍历人名，将其中的换行符去掉
        for (int i = 0; i < wcslen(player2); i++)
        {
            if (player2[i] == L'\n')
            {
                player2[i] = L'·';
            }
        }
        player2[wcslen(player2) - 1] = L'\0';
        // 人机对战
        Game_Start();
    }
    else if (x1 >= 54 + (bufferSize.X - 54 - 12) / 2 && x1 <= 54 + (bufferSize.X - 54 - 12) / 2 + 12 && y1 == bufferSize.Y / 2 + 8)
    {
        // 退出游戏
        exit(0);
    }
    else
    {
        // 重新获取鼠标输入
        goto LABEL1;
    }
}

void MapColorTable()
{
    CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
    csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfoEx(hOut, &csbiex);
    csbiex.ColorTable[0] = RGB(41, 97, 136);   // 替代黑色
    csbiex.ColorTable[1] = RGB(240, 200, 183); // 替代白色，落子强调色
    SetConsoleScreenBufferInfoEx(hOut, &csbiex);
}

void WaitLeftClick()
{
    // 等待鼠标点击
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);
    ClearScreen();
}

void Print_Grandient_Logo()
{
    srand((unsigned)time(NULL));
    // 生成一个随机颜色，使用struct Color，作为渐变起始色
    struct Color startColor = (struct Color){rand() % 256, rand() % 256, rand() % 256};
    // 生成一个随机颜色，使用struct Color，作为渐变终止色
    struct Color endColor = (struct Color){rand() % 256, rand() % 256, rand() % 256};
    // 生成一个渐变色数组，用于渐变
    struct Color gradient[25];
    for (int i = 0; i < 25; i++)
    {
        gradient[i] = (struct Color){startColor.r + (endColor.r - startColor.r) * i / 25, startColor.g + (endColor.g - startColor.g) * i / 25, startColor.b + (endColor.b - startColor.b) * i / 25};
    }
    for (int i = 0; i < 25; i++)
    {
        Console_Print_Prefix(logo[i], gradient[i], bufferSize.X * 0.1, (bufferSize.Y - 24) / 2 + i);
    }
}

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