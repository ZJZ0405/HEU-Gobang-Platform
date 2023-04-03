#include "base.h"

/**
 * @brief 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
 *
 */
void getValuableBlank(int board[][15], Chess *chess, int *length)
{
    int i, j, k, l, m, n;
    int count = 0;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (board[i][j] == 0)
            {
                for (k = i - 2; k <= i + 2; k++)
                {
                    for (l = j - 2; l <= j + 2; l++)
                    {
                        if (k >= 0 && k < 15 && l >= 0 && l < 15)
                        {
                            if (board[k][l] == 1 || board[k][l] == 2)
                            {
                                chess[count].x = j - 7;
                                chess[count].y = i - 7;
                                chess[count].type = EMPTY;
                                count++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}