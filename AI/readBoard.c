#include "base.h"

/**
 * @brief 读取棋盘中数据
 * @param board[15][15] 棋盘
 * @param x
 * @param y
 * @return 值
 */
Type readBoard(const int board[15][15], const int x, const int y)
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
    return *((int *)board + 15 * (7 - y) + x + 7);
}