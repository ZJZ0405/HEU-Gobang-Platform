#include "base.h"

/**
 * @brief 写入数据到棋盘
 * @param board[15][15] 棋盘
 * @param x x
 * @param y y
 * @param type 种类
 * @return 是否成功写入
 */
bool writeBoard(int board[15][15], const int x, const int y, Type type)
{
    if (NULL == board)
    {
        printf("ERROR - board of point is NULL!");
        return false;
    }
    *((int *)board + 15 * (7 - y) + x + 7) = type;

    return true;
}