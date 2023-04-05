#include "base.h"

/**
 * @brief 读取棋盘中数据
 * @param board[15][15] 棋盘
 * @param x
 * @param y
 * @return 值
 */
Type readBoard(int **board, int x, int y)
{
    if (NULL == board)
    {
        printf("ERROR - board of point is NULL!");
        return -1;
    }
    if (x < -7 && x > 7 && y < -7 && y > 7)
    {
        printf("ERROR - point is not in board");
        return -2;
    }

    //wprintf(L"\x1b[38;2;%d;%d;%dm readBoard accessing board[%d][%d] = %d\n",255,255,255, x, y, board[-1 * y + 7][x + 7]);
    return board[-1 * y + 7][x + 7];

    /* int(*p)[15] = board;
    return *(*(p - x + 7) + y + 7); */
}