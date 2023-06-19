#include <stdio.h>
#include "base.h"
#include "AI/AI.h"

int main(void)
{
    printf("helloworld\n");
    int **board = (int **)calloc(sizeof(int *), 15);
    for (int i = 0; i < 15; i++)
    {
        board[i] = (int *)calloc(sizeof(int), 15);
    }
    while (true)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        if (EMPTY != readBoard((const int**)board, x, y))
        {
            printf("re-put\n");
            continue;
        }
        if (false == writeBoard(board, x, y, WHITE))
        {
            printf("re-put\n");
            continue;
        }
        
        for (int i = -7; i < -1; i++)
        {
            printf("%d", i);
        }
        for (int i = 0; i <= 7; i++)
        {
            printf(" %d", i);
        }
        printf("\n");
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (EMPTY == board[i][j])
                {
                    printf("  ");
                }
                else if (WHITE == board[i][j])
                {
                    printf("O ");
                }
                else if (BLACK == board[i][j])
                {
                    printf("X ");
                }
            }
            printf("\n");
        }
        printf("================================\n");
        printf("%d\n=====\n", evaluateGobalScore((const int**)board, BLACK));
        int deepth = 2;
        Chess next_chess = {0};
        DFS(board, deepth, BLACK, &next_chess);
        writeBoard(board, next_chess.x, next_chess.y, BLACK);
        printf("  ");
        for (int i = -7; i < 0; i++)
        {
            printf("%d", i);
        }
        for (int i = 0; i <= 7; i++)
        {
            printf(" %d", i);
        }
        printf("\n");
        for (int i = 0; i < 15; i++)
        {
            if (0 > -(i - 7))
            {
                printf("%d", -(i - 7));
            }
            else
            {
                printf(" %d", -(i - 7));
            }
            for (int j = 0; j < 15; j++)
            {
                if (EMPTY == board[i][j])
                {
                    printf("  ");
                }
                else if (WHITE == board[i][j])
                {
                    printf(" O");
                }
                else if (BLACK == board[i][j])
                {
                    printf(" X");
                }
            }
            printf("\n");
        }
        printf("================================\n");
        printf("%d\n=====\n", evaluateGobalScore((const int**)board, BLACK));
    }
    

    return 0;
}