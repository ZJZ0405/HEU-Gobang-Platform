#include "base.h"

/**
 * @brief 评估当前全局分数
 * @param board[15][15] 当前棋盘
 * @param self_type 己方棋子颜色
 * @return 评估得分
 */
int evaluateGobalScore(const int board[15][15], const Type self_type)
{
    if (NULL == board)
    {
        printf("ERROR - board of point is NULL!");
        return -1;
    }
    const Type ENEMY_COLOR = (BLACK == self_type) ? WHITE : BLACK; //敌人
    
    Count self = {0};
    Count enemy = {0};

    //x轴
    for (int y = -7; y <= 7; y++)
    {
        int array[15] = {0};
        for (int x = -7; x <= 7; x++)
        {
            array[x+7] = readBoard(board, x, y);
        }
        countUnit(array, 15, self_type, &self, &enemy);
    }
    //y轴
    for (int x = -7; x <= 7; x++)
    {
        int array[15] = {0};
        for (int y = -7; y <= 7; y++)
        {
            array[y+7] = readBoard(board, x, y);
        }
        countUnit(array, 15, self_type, &self, &enemy);
    }
    //主对角线方向
    {
        for (int y = -7; y <= 7; y++)
        {
            int array[15] = {0};
            int i = 0;
            int _y = y;
            for (int x = -7;x >= -7 && x <= 7 && _y >= -7 && _y <= 7;x++,_y++)
            {
                array[i] = readBoard(board, x, _y);
                i++;
            }
            countUnit(array, i, self_type, &self, &enemy);
        }
        for (int x = -6; x <= 7; x++)
        {
            int array[15] = {0};
            int i = 0;
            int _x = x;
            for (int y = -7;x >= -7 && x <= 7 && _x >= -7 && _x <= 7;y++,_x++)
            {
                array[i] = readBoard(board, _x, y);
                i++;
            }
            countUnit(array, i, self_type, &self, &enemy);
        }
    }
    //副对角线方向
    {
        for (int y = -7; y <= 7; y++)
        {
            int array[15] = {0};
            int i = 0;
            int _y = y;
            for (int x = 7;x >= -7 && x <= 7 && _y >= -7 && _y <= 7;x--,_y++)
            {
                array[i] = readBoard(board, x, _y);
                i++;
            }
            countUnit(array, i, self_type, &self, &enemy);
        }
        for (int x = 6; x >= -7; x--)
        {
            int array[15] = {0};
            int i = 0;
            int _x = x;
            for (int y = -7;x >= -7 && x <= 7 && _x >= -7 && _x <= 7;y++,_x--)
            {
                array[i] = readBoard(board, _x, y);
                i++;
            }
            countUnit(array, i, self_type, &self, &enemy);
        }
    }

    // if (1 <= self.con_five)
    // {
    //     return -1;
    // }
    // else if (1 <= enemy.con_five)
    // {
    //     return -2;
    // }
    int output = self.con_five * 1000000
                 +self.active_four * 10000
                 +self.active_three * 1000
                 +self.active_two * 100
                 +self.active_one *10
                 +self.inactive_four * 1000
                 +self.inactive_three * 100
                 +self.inactive_two * 10
                 
                 -enemy.con_five * 1000000
                 -enemy.active_four * 10000
                 -enemy.active_three * 1000
                 -enemy.active_two * 100
                 -enemy.active_one *10
                 -enemy.inactive_four * 1000
                 -enemy.inactive_three * 100
                 -enemy.inactive_two * 10;
    return output;
}