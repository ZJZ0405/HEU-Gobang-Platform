#include "base.h"

/**
 * @brief 写入数据到棋盘
 * @param board[15][15] 棋盘
 * @param x x
 * @param y y
 * @param type 种类
 * @return 是否成功写入
 */
bool writeBoard(int **board, int x, int y, Type type)
{
    if (NULL == board)
    {
        printf("ERROR - board of point is NULL!");
        return false;
    }
    //wprintf(L"\x1b[38;2;%d;%d;%dm writeBoard accessing board[%d][%d] = %d\n",255,255,255, x, y, board[-1 * y + 7][x + 7]);
    board[-1 * y + 7][x + 7] = type;

    return true;
}