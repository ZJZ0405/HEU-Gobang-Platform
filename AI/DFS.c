#include "base.h"
#include <limits.h>

/**
 * @brief 深度优先搜索，寻找落子位置
 * @param board[15][15] 棋盘,请传入棋盘深拷贝副本
 * @param deepth 搜索深度
 * @param type 己方阵营
 * @return 分数
*/
int DFS(int** board, int deepth, Type type, Chess *next_chess)
{
    if (0 == deepth)
    {
        return evaluateGobalScore(board, type);
    }
    else
    {
        int _deepth = deepth - 1;
        int length = 0;
        Chess chesses[225] = {0};
        getValuableBlank(board, chesses, &length); //落子位置集合
        writeBoard(board, chesses[0].x, chesses[0].y, type);
        Chess _next_chess = {0};
        int max_sorce = DFS(board, _deepth, type*(-1), &_next_chess);
        max_sorce *= (-1);
        writeBoard(board, chesses[0].x, chesses[0].y, EMPTY);
        int tag = 0;
        for (int i = 1; i < length; i++)
        {
            writeBoard(board, chesses[i].x, chesses[i].y, type);
            Chess _next_chess = {0};
            int sorce = DFS(board, _deepth, type*(-1), &_next_chess);
            sorce *= (-1);
            writeBoard(board, chesses[i].x, chesses[i].y, EMPTY);
            if (sorce >= max_sorce)
            {
                max_sorce = sorce;
                tag = i;
            }
        }
        next_chess->x = chesses[tag].x;
        next_chess->y = chesses[tag].y;
        next_chess->type = type;
        return max_sorce;
    }   
}