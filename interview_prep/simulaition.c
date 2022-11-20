
#include <stdio.h>
int DevilsChessboard(char devil_board[], int magic_coin)
{
    char coin_to_flip = 0;
    int sum_of_ones = 0;

    int i = 0;

    for (i = 0; i < 64; ++i)
    {
        if (devil_board[i] == 1)
        {
            sum_of_ones += i;
        }
    }

    coin_to_flip = ((64 - (sum_of_ones % 64)) + magic_coin) % 64;

    return coin_to_flip;
}

int main()
{
    char devil_board[64] = {0};
    devil_board[5] = 1;
    devil_board[62] = 1;
    devil_board[14] = 1;
    devil_board[43] = 1;
    devil_board[23] = 1;
    devil_board[2] = 1;

    printf("coin to flip: %d\n", DevilsChessboard(devil_board, 21));
    return 0;
}
