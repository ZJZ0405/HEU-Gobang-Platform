#pragma once
/**
 * @param BLACK 黑棋
 * @param WHITE 白棋
 * @param EMPTY 空
 */
typedef enum
{
    BLACK = 1,  // 黑棋
    WHITE = -1, // 白棋
    EMPTY = 0   // 空
} Type;

/**
 * @brief 棋子位置
 * @param x
 * @param y
 * @param color 颜色
 */
typedef struct
{
    int x;
    int y;
    Type type;
} Chess;

/**
 * @brief 连子状态
 * @param CON_FIVE 连五
 * @param ACTIVE_FOUR 活四
 * @param ACTIVE_THREE 活三
 * @param ACTIVE_TWO 活二
 * @param ACTIVE_ONE 活一
 * @param INACTIVE_FOUR 死四
 * @param INACTIVE_THREE 死三
 * @param INACTIVE_TWO 死二
 */
typedef enum
{
    CON_FIVE,
    ACTIVE_FOUR,
    ACTIVE_THREE,
    ACTIVE_TWO,
    ACTIVE_ONE,

    INACTIVE_FOUR,
    INACTIVE_THREE,
    INACTIVE_TWO
} Grade;

/**
 * @brief 连子状态数量
 * @param con_five 连五
 * @param active_four 活四
 * @param active_three 活三
 * @param active_two 活二
 * @param active_one 活一
 * @param inactive_four 死四
 * @param inactive_three 死三
 * @param inactive_two 死二
 */
typedef struct
{
    int con_five;
    int active_four;
    int active_three;
    int active_two;
    int active_one;

    int inactive_four;
    int inactive_three;
    int inactive_two;
} Count;

