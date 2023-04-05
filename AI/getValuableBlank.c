#include "base.h"

/**
 * @brief 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
 * @param board[15][15] 棋盘
 * @param chess 接收棋子列表
 * @param length 接收棋子数量
 */
void getValuableBlank(int board[15][15], Chess *chess, int *length)
{
     int count = 0;
     for (int x = -7; x < 7; x++)
     {
         for (int y = -7; y < 7; y++)
         {
             if (EMPTY == readBoard(board, x, y))
             {
                 for (int _x = x - 2; _x <= x + 2 && _x >= -7 && _x <= 7; _x++)
                 {
                     for (int _y = y - 2; _y <= y + 2 && _y >= -7 && _y <= 7; _y++)
                     {
                         
                        if (EMPTY != readBoard(board, _x, _y))
                        {
                            (chess+count)->x = x;
                            (chess+count)->y = y;
                            (chess+count)->type = EMPTY;
                            count++;
                            break;
                        }
                     }
                 }
             }
         }
     }
     *length = count;
    // 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
    // 返回值为找到的空位的个数
    /* int x, y;
    int count = 0;
    for (x = -7; x < 7; x++)
    {
        for (y = -7; y < 7; y++)
        {
            if (0 == readBoard(board, x, y))
            {
                if (x - 1 >= 0 && 0 != readBoard(board, x-1, y))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x-1, y);
                    count++;
                }
                else if (x + 1 < 7 && 0 != readBoard(board, x+1, y))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x+1, y);
                    count++;
                }
                else if (y - 1 >= -7 && 0 != readBoard(board, x, y-1))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x, y-1);
                    count++;
                }
                else if (y + 1 < 7 && 0 != readBoard(board, x, y+1))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x, y+1);
                    count++;
                }
                else if (x - 1 >= -7 && y - 1 >= -7 && 0 != readBoard(board, x-1, y-1))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x-1, y-1);
                    count++;
                }
                else if (x - 1 >= -7 && y + 1 < 7 && 0 != readBoard(board, x-1, y+1))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x-1, y+1);
                    count++;
                }
                else if (x + 1 < 7 && y - 1 >= -7 && readBoard(board, x+1, y-1))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x+1, y-1);
                    count++;
                }
                else if (x + 1 < 7 && y + 1 < 7 && 0 != readBoard(board, x+1, y+1))
                {
                    chess[count].x = x;
                    chess[count].y = y;
                    chess[count].type = readBoard(board, x+1, y+1);
                    count++;
                }
            }
        }
    }
    *length = count;
    return count; */
}