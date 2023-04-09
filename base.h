#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

/**
 * @brief 封装函数
 * @version 0.1.0
 * @param board[15][15] 棋盘
 * @param self_type 己方颜色
 * @param in 当前敌方落子位置
 * @param out 己方落子位置
 */
void ProcessNext(const int **board, Type self_type, Chess *in, Chess *out);

/**
 * @brief 读取棋盘中数据
 * @param board[15][15] 棋盘
 * @param x
 * @param y
 * @return 该坐标下棋盘上棋子的类型
 */
static inline Type readBoard(const int **board, const int x, const int y)
{
    if (NULL == board)
    {
        printf("ERROR - board of point is NULL!");
        return -1;
    }
    if (x < -7 || x > 7 || y < -7 || y > 7)
    {
        printf("ERROR - point is not in board");
        return -2;
    }
    // fix capability to separate array
    return board[-1 * y + 7][x + 7];
}
/**
 * @brief 写入数据到棋盘
 * @param board[15][15] 棋盘
 * @param x x
 * @param y y
 * @param type 种类
 * @return 是否成功写入
 */
static inline bool writeBoard(int **board, const int x, const int y, Type type)
{
    if (NULL == board)
    {
        printf("ERROR - board of point is NULL!");
        return false;
    }
    if (x < -7 || x > 7 || y < -7 || y > 7)
    {
        printf("ERROR - point is not in board");
        return false;
    }
    // fix capability to separate array
    board[-1 * y + 7][x + 7] = type;

    return true;
}
/**
 * @brief 判断连子类型
 * @param length 长度
 * @param first_status 开始是否阻塞
 * @param end_status 结束是否阻塞
 * @return 连子类型
 */
Grade judgeStatus(int length, bool first_status, bool end_status);

/**
 * @brief 计算单元
 * @param array[] 一维数组
 * @param array_lenght 数组长度
 * @param self_type 己方种类
 * @param self 己方分数类型记分
 * @param enemy 敌方分数类型记分
 */
void countUnit(const int array[], const int array_lenght, const Type self_type, Count *self, Count *enemy);

/**
 * @brief 评估当前全局分数
 * @param board[15][15] 当前棋盘
 * @param self_type 己方棋子颜色
 * @return 评估得分
 */
int evaluateGobalScore(const int **board, const Type self_type);

/**
 * @brief 评估当前单步分数
 * @param board[15][15] 当前棋盘
 * @param self_type 己方棋子颜色
 * @param in 新加入的步骤
 * @return 评估得分
 */
int evaluateScore(const int **board, const Type self_type, const Chess *in);

/**
 * @brief 找出棋盘中距离棋子距离小于等于2的所有空位，并通过chess数组传出，chess数组的长度为length
 * @param board[15][15] 棋盘
 * @param chess 接收棋子列表
 * @param length 接收棋子数量
 */
void getValuableBlank(int **board, Chess *chess, int *length);

/**
 * @brief DFS节点
 * @param chess 棋子
 * @param score 得分
 */
typedef struct
{
    Chess chess;
    int score;
} Node;

/**
 * @brief 深度优先搜索，寻找落子位置
 * @param board[15][15] 棋盘,请传入棋盘深拷贝副本
 * @param deepth 搜索深度
 * @param type 己方阵营
 * @return 分数
 */
int DFS(int **board, int deepth, Type type, Chess *next_chess);
