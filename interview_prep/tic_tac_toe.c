#include <stdio.h>

int main()
{
    /* char name1[20] = "";
    char name2[20] = ""; */
    int indexes[2] = {0};
    int chart[3][3] = {0};
    int counter = 0;
    int turn = 0;
    int is_win = 0;
    int turn_num = 0;
    int i, j, x;
    int possible_win[8][3][2] = {
        {{0, 0}, {0, 1}, {0, 2}},
        {{1, 0}, {1, 1}, {1, 2}},
        {{2, 0}, {2, 1}, {2, 2}},
        {{0, 0}, {1, 0}, {2, 0}},
        {{0, 1}, {1, 1}, {2, 1}},
        {{0, 2}, {1, 2}, {2, 2}},
        {{0, 0}, {1, 1}, {2, 2}},
        {{2, 0}, {1, 1}, {0, 2}},
    };

    /* greetings: */
    printf("Hello and welcome\n\n\n");

    /* explain the game to the users: */
    printf("this is the TIC TAC TOE game:\n\n\n");

    /* get players name:
    printf("Player 1 name:\n");
    scanf("%s", name1);
    printf("Player 2 name:\n");
    scanf("%s", name2);*/

    /* drow starting player: */
    turn = 1;
    /* start game */
    while (is_win == 0 && turn_num < 9)
    {
        /* draw chard board: */
        printf("Current board:\n");
        printf("__________________\n\n");
        for (j = 0; j < 3; j++)
        {
            printf("     ");
            for (x = 0; x < 3; ++x)
            {
                printf("%d ", chart[j][x]);
            }
            printf("\n");
        }
        printf("__________________\n");
        printf("\n");

        turn = !turn;
        printf("player %d turn.\n", turn + 1);

        /* take cell location */
        printf("please enter row index:\n");
        scanf("%d", &indexes[0]);
        printf("please enter col index:\n");
        scanf("%d", &indexes[1]);
        printf("\n");

        /* validate */
        if (indexes[0] > 2 || indexes[1] > 2 || chart[indexes[0]][indexes[1]] != 0)
        {
            printf("invalid index, enter new index!\n\n");
            turn = !turn;
            continue;
        }

        /* mark cell */
        chart[indexes[0]][indexes[1]] = (turn + 1);

        /* chaeck win */

        for (i = 0; i < 8; ++i)
        {
            counter = 0;
            for (j = 0; j < 3; j++)
            {
                if (chart[possible_win[i][j][0]][possible_win[i][j][1]] == 0 ||
                    chart[possible_win[i][j][0]][possible_win[i][j][1]] == ((!turn) + 1))
                {
                    break;
                }
                ++counter;
            }
            if (counter == 3)
            {
                is_win = 1;
                break;
            }
        }
        ++turn_num;
    }

    if (is_win == 0)
    {
        printf(" NO one wins, play again ! \n");
    }

    printf("player %d win!!\n", turn + 1);

    return 0;
}