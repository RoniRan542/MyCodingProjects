/*Author: Ran Aharon Cohen
 Date: 02.06.22
 Reviewed By: Karen
 */
#include <time.h>	/* for time */
#include <assert.h> /*for assert */
#include <stdlib.h> /* for exit */

#include "../include/bit_array.h" /* using bit_array funcs */

#define SQUARES_IN_BOARD (64)
#define MAX_OPS (8)
#define VISITED (1)
#define INVALID (-1)
#define FIVE_MIN (5)
#define SQUARES_IN_LINE (8)
#define TESTED_OPT (-1)

enum status
{
	SUCCESS = 0,
	FAILURE
};

enum bit_val
{
	OFF = 0,
	ON
};

static int TakeValidNextMove(int current_position, int index);
static int TakeNextMove(int current_position, int index);
static void SignOptionAsTested(int *move);
static void InitMovesLut(void);
static int GetValidMove(int i, int j);
static int RecKnightTour(int current_position, bit_arr_t board, int *tour);
static int RecKnightTourWarnsdorff(int current_position, bit_arr_t board, int *tour);
static int MinOptNextMove(int current_position, bit_arr_t board, int *option_tested_lut);
static void DecreaseCountAtPrevMovesLut(int next_move);
static void UpdateConnectionOptions(int position, int update);
static int g_count_opt_lut[SQUARES_IN_BOARD] = {0};
static int g_moves_lut[SQUARES_IN_BOARD][MAX_OPS] = {0};
static const int g_two_one_steps[SQUARES_IN_LINE][2] = {
	{16, 1}, {8, 2}, {-8, 2}, {-16, 1}, {-16, -1}, {-8, -2}, {8, -2}, {16, -1}};

static time_t start_time = 0;

int KnightTour(int start_index, int *buffer)
{
	bit_arr_t board = 0;

	assert(0 <= start_index);
	assert(SQUARES_IN_BOARD > start_index);
	assert(NULL != buffer);

	InitMovesLut();
	start_time = time(0);

	return RecKnightTourWarnsdorff(start_index, board, buffer);
}

static int RecKnightTour(int current_position, bit_arr_t board, int *tour)
{
	int status = 0;
	int i = 0;
	int next_move = 0;

	board = BitArrSetBitOn(board, (uint64_t)current_position);

	if (SQUARES_IN_BOARD == BitArrCountOn(board))
	{
		*tour = current_position;

		return SUCCESS;
	}

	if (FIVE_MIN < (time(0) - start_time))
	{
		exit(0);
	}

	for (i = 0; i < MAX_OPS; ++i)
	{
		next_move = TakeValidNextMove(current_position, i);
		if (INVALID < next_move && VISITED != BitArrGetBitVal(board, next_move))
		{
			status = RecKnightTour(next_move, board, tour + 1);
			if (SUCCESS == status)
			{
				*tour = current_position;

				return status;
			}
		}
	}

	return FAILURE;
}

static int RecKnightTourWarnsdorff(int current_position,
								   bit_arr_t board, int *tour)
{
	int next_move = 0;
	int move_index = 0;
	int i = 0;
	int option_tested_lut[MAX_OPS] = {0};

	board = BitArrSetBitOn(board, (uint64_t)current_position);

	UpdateConnectionOptions(current_position, -1);

	if (SQUARES_IN_BOARD == BitArrCountOn(board))
	{
		*tour = current_position;

		return SUCCESS;
	}

	for (i = 0; i < MAX_OPS; ++i)
	{
		move_index = MinOptNextMove(current_position, board, option_tested_lut);
		if (INVALID == move_index)
		{
			return FAILURE;
		}

		next_move = TakeNextMove(current_position, move_index);

		SignOptionAsTested(&option_tested_lut[move_index]);

		if (SUCCESS == RecKnightTourWarnsdorff(next_move, board, tour + 1))
		{
			*tour = current_position;

			return SUCCESS;
		}
		UpdateConnectionOptions(next_move, 1);
	}

	return FAILURE;
}

static void UpdateConnectionOptions(int position, int update)
{
	int move = 0;
	int curr_opt = 0;

	for (move = 0; MAX_OPS > move; ++move)
	{
		curr_opt = TakeValidNextMove(position, move);
		if (0 <= curr_opt)
		{
			g_count_opt_lut[position] += update;
		}
	}
}

static int MinOptNextMove(int current_position, bit_arr_t board, int *option_tested_lut)
{
	int min = MAX_OPS;
	int move_index = INVALID;
	int curr_opt = 0;
	int i = 0;

	for (i = 0; i < MAX_OPS; ++i)
	{
		curr_opt = TakeValidNextMove(current_position, i);

		if ((0 <= curr_opt) && (ON != BitArrGetBitVal(board, curr_opt)) &&
			TESTED_OPT != option_tested_lut[i])
		{
			if (min >= g_count_opt_lut[curr_opt])
			{
				min = g_count_opt_lut[curr_opt];
				move_index = i;
			}
		}
	}

	return move_index;
}

static int TakeValidNextMove(int current_position, int index)
{
	int found = INVALID;

	if (0 <= g_moves_lut[current_position][index])
	{
		return g_moves_lut[current_position][index];
	}

	return found;
}

static int TakeNextMove(int current_position, int index)
{
	return g_moves_lut[current_position][index];
}

static void InitMovesLut()
{
	int i = 0;
	int j = 0;
	char count = 0;

	for (i = 0; i < SQUARES_IN_BOARD; ++i)
	{
		count = 0;
		for (j = 0; j < SQUARES_IN_LINE; ++j)
		{

			g_moves_lut[i][j] = GetValidMove(i, j);
			if (0 <= g_moves_lut[i][j])
			{
				++count;
			}
		}
		g_count_opt_lut[i] = count;
	}
}

static void SignOptionAsTested(int *move)
{
	*move = -1;
}

static int GetValidMove(int i, int j)
{
	int temp = (i + g_two_one_steps[j][0]);

	if ((0 <= temp) && (SQUARES_IN_BOARD > temp))
	{
		if (temp < ((temp + g_two_one_steps[j][1])))
		{
			if ((temp % SQUARES_IN_LINE) <
				((temp + g_two_one_steps[j][1]) % SQUARES_IN_LINE))
			{
				return (temp + g_two_one_steps[j][1]);
			}
		}
		else
		{
			if ((temp % SQUARES_IN_LINE) >
				((temp + g_two_one_steps[j][1]) % SQUARES_IN_LINE))
			{
				return (temp + g_two_one_steps[j][1]);
			}
		}
	}

	return INVALID;
}
