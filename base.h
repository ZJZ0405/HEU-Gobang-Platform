#include <stdio.h>
#include <stdbool.h>

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
}Count;

/**
 * @brief 封装函数
 * @version 0.1.0
 * @param board 棋盘
 * @param self_type 己方颜色
 * @param in 当前敌方落子位置
 * @param out 己方落子位置
 */
void ProcessNext(const int board[15][15], Type self_type, Chess *in, Chess *out);

/**
 * @brief 读取棋盘中数据
 * @param board[][15] 棋盘
 * @param x
 * @param y
 * @return 该坐标下棋盘上棋子的类型
 */
Type readBoard(const int board[15][15], const int x, const int y);

/**
 * @brief 判断连子类型
 * @param length 长度
 * @param type 棋子类型
 * @param first_status 开始是否阻塞
 * @param end_status 结束是否阻塞
 * @return 连子类型
*/
Grade judgeStatus(int length, Type type, bool first_status, bool end_status);

/**
 * @brief 评估当前全局分数
 * @param board 当前棋盘
 * @param self_type 己方棋子颜色
 * @return 评估得分
 */
int evaluateGobalScore(const int board[15][15], const Type self_type);

/**
 * @brief 评估当前单步分数
 * @param board 当前棋盘
 * @param self_type 己方棋子颜色
 * @param in 新加入的步骤
 * @return 评估得分
 */
int evaluateScore(const int board[15][15], const Type self_type, const Chess *in);