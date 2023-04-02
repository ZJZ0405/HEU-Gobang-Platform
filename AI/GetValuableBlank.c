#include "base.h"

typedef struct
{
    int x;
    int y;
    Color color;
} Chess;

enum Color
{
    BALNK,
    BLACK,
    WHITE,
};
/**
 * @brief 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
 *
 */
int GetValuableBlank(int board[][15], Chess *chess, int *length)
{
    // 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
    // 返回值为找到的空位的个数
    int i, j;
    int count = 0;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (board[i][j] == 0)
            {
                if (i - 1 >= 0 && board[i - 1][j] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i - 1][j];
                    count++;
                }
                else if (i + 1 < 15 && board[i + 1][j] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i + 1][j];
                    count++;
                }
                else if (j - 1 >= 0 && board[i][j - 1] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i][j - 1];
                    count++;
                }
                else if (j + 1 < 15 && board[i][j + 1] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i][j + 1];
                    count++;
                }
                else if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i - 1][j - 1];
                    count++;
                }
                else if (i - 1 >= 0 && j + 1 < 15 && board[i - 1][j + 1] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i - 1][j + 1];
                    count++;
                }
                else if (i + 1 < 15 && j - 1 >= 0 && board[i + 1][j - 1] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i + 1][j - 1];
                    count++;
                }
                else if (i + 1 < 15 && j + 1 < 15 && board[i + 1][j + 1] != 0)
                {
                    chess[count].x = i;
                    chess[count].y = j;
                    chess[count].color = board[i + 1][j + 1];
                    count++;
                }
            }
        }
    }
    *length = count;
}