#include "base.h"
#include <limits.h>

/**
 * @brief 深度优先搜索，寻找落子位置
 * @param board[15][15] 棋盘,请传入棋盘深拷贝副本
 * @param deepth 搜索深度
*/
Node DFS(int board[15][15], Chess chess,int deepth)
{
    if (0 >= deepth)
    {
        Node end_node = {0};
        writeBoard(board, chess.x, chess.y, chess.type);
        end_node.chess = chess;
        end_node.score = evaluateGobalScore(board, chess.type);
        end_node.score *= (-1);
        writeBoard(board, chess.x, chess.y, EMPTY);
        //printf("*");
        return end_node;
    }
    else
    {
        Chess chesses[225] = {0};
        int length = 0;
        Node node = {0};
        
        getValuableBlank(board, chesses, &length);
        int _deepth = deepth - 1;
        {
            writeBoard(board, chesses[0].x, chesses[0].y, chesses[0].type);
            node = DFS(board, chesses[0], _deepth);
            node.score *= (-1);
            
            writeBoard(board, chesses[0].x, chesses[0].y, EMPTY);
        }
        for (int i = 1; i < length; i++)
        {
            writeBoard(board, chesses[i].x, chesses[i].y, chesses[i].type);
            Node _node = DFS(board, chesses[i], _deepth);
            _node.score *= (-1);
            if (_node.score > node.score)
            {
                node = _node;
            }
            writeBoard(board, chesses[i].x, chesses[i].y, EMPTY);
        }
        
        //printf("#");
        return node;
    }

    
}