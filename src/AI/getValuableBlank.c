#include "AI.h"

/**
 * @brief 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
 * @param board** 棋盘
 * @param chess 接收棋子列表
 * @param length 接收棋子数量
 */
void getValuableBlank(const int** board, Chess *chess, int *length)
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
}