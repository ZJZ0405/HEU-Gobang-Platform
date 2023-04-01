#include <stdio.h>

/**
 * @param BLACK 黑棋
 * @param WHITE 白棋
 * @param EMPTY 空
 */
typedef enum
{
    BLACK = 1, // 黑棋
    WHITE = 2, // 白棋
    EMPTY = 0  // 空
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
    CON_FIVE = 100000,
    ACTIVE_FOUR = 10000,
    ACTIVE_THREE = 1000,
    ACTIVE_TWO = 100,
    ACTIVE_ONE = 10,

    INACTIVE_FOUR = 1000,
    INACTIVE_THREE = 100,
    INACTIVE_TWO = 10
} Grade;

/**
 * @brief 封装函数
 * @version 0.1.0
 */
void ProcessNext(const int board[15][15], Type self_color, Chess *in, Chess *out); // bw为己方颜色

/**
 * @brief 读取棋盘中数据
 * @param board[][15] 棋盘
 * @param x
 * @param y
 * @return 值
 */
int readBoard(const int board[15][15], const int x, const int y);

/**
 * @brief 评估当前全局分数
 * @param board 当前棋盘
 * @param bw 己方棋子颜色
 * @return 评估得分
 */
int evaluateGobalScore(const int board[15][15], const Type self_type);

/**
 * @brief 评估当前单步分数
 * @param board 当前棋盘
 * @param bw 己方棋子颜色
 * @param in 新加入的步骤
 * @return 评估得分
 */
int evaluateScore(const int board[15][15], const Type self_type, const Chess *in);