#include <stdio.h>
#include <stdlib.h>

#define BLANK '.'
#define BLACK '@'
#define WHITE 'O'

struct state
{
    char player, elements[8][8];
    int minmax_val[2];
    struct state *childs[64];
};
typedef struct state state_t;

/* Check make flip at least one opponent piece or not */
int
would_flip(state_t state, char opp, int i, int j, int *dir)
{
    int ret_val = -1;
    for (int k = 1; state.elements[i + k][j] == opp && i + k < 7; k++)
        if (state.elements[i + k + 1][j] == BLANK)
        {
            dir[0] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i - k][j] == opp && i - k > 0; k++)
        if (state.elements[i - k - 1][j] == BLANK)
        {
            dir[1] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i][j - k] == opp && j - k > 0; k++)
        if (state.elements[i][j - k - 1] == BLANK)
        {
            dir[2] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i][j + k] == opp && j + k < 7; k++)
        if (state.elements[i][j + k + 1] == BLANK)
        {
            dir[3] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i + k][j + k] == opp && i + k < 7 && j + k < 7; k++)
        if (state.elements[i + k + 1][j + k + 1] == BLANK)
        {
            dir[4] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i - k][j - k] == opp && i - k > 0 && j - k > 0; k++)
        if (state.elements[i - k - 1][j - k - 1] == BLANK)
        {
            dir[5] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i - k][j + k] == opp && i - k > 0 && j + k < 7; k++)
        if (state.elements[i - k - 1][j + k + 1] == BLANK)
        {
            dir[6] = k;
            ret_val = 1;
        }
    for (int k = 1; state.elements[i + k][j - k] == opp && i + k < 7 && j - k > 0; k++)
        if (state.elements[i + k + 1][j - k - 1] == BLANK)
        {
            dir[7] = k;
            ret_val = 1;
        }
    return ret_val;
}

/* Check a state is terminal node or not */
int is_terminal(state_t state)
{
    int dir[8] = {-1};
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (state.elements[i][j] != BLANK)
            {
                char opp = state.elements[i][j] == BLACK ? WHITE : BLACK;
                if (would_flip(state, opp, i, j, dir) == 1)
                    return -1;
            }
    return 1;
}

/* Utility function */
void utility(state_t state, int *black, int *white)
{
    int sum_black = 0, sum_white = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (state.elements[i][j] == BLACK)
                sum_black++;
            else if (state.elements[i][j] == WHITE)
                sum_white++;
    *black = sum_black;
    *white = sum_white;
}

/* Copy two state elements */
void copy_state(state_t *src, state_t *dest)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            dest->elements[i][j] = src->elements[i][j];
}

/* Update board with opp flips */
/* mode : 0 for horizontal, 1 for vertical, 2 for diagonal */
void make_flips(state_t *state, char player, int i, int j, int k, int mode)
{
    switch (mode)
    {
        case 0:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i + m][j] = player;
            break;
        case 1:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i - m][j] = player;
            break;
        case 2:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i][j - m] = player;
            break;
        case 3:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i][j + m] = player;
            break;
        case 4:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i + m][j + m] = player;
            break;
        case 5:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i - m][j - m] = player;
            break;
        case 6:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i - m][j + m] = player;
            break;
        case 7:
            for (int m = 1; m <= k + 1; m++)
                state->elements[i + m][j - m] = player;
            break;
        default:
            break;
    }
}

/* Fill a state childs */
void fill_childs(state_t *state)
{
    int n = 0, dir[8] = {-1};
    char opp = state->player == WHITE ? BLACK : WHITE;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (state->elements[i][j] == state->player)
            {
                if (would_flip(*state, opp, i, j, dir) == 1)
                {
                    for (int q = 0; q < 8; q++)
                        if (dir[q] != -1)
                        {
                            state->childs[n] = (state_t *) malloc(sizeof(state_t));
                            copy_state(state, state->childs[n]);
                            state->childs[n]->player = opp;
                            make_flips(state->childs[n], state->player, i, j, dir[q], q);
                            n++;
                        }
                }
            }
}

/* Print a state */
void print_state(state_t state)
{
    printf("\t   \033[1;33m1  2  3  4  5  6  7  8\033[0m\n");
    for (int i = 0; i < 8; i++)
    {
        printf("\t\033[1;33m%d\033[0m  %c", i + 1, state.elements[i][0]);
        for (int j = 1; j < 8; j++)
            printf("  %c", state.elements[i][j]);
        printf("\n");
    }
}

/* Is valid move */
int valid_move(state_t state, char player, int i, int j)
{
    if (i < 0 || j < 0 || i > 7 || j > 7)
        return -1;
    char opp = state.elements[i][j] == BLACK ? WHITE : BLACK;
    if (state.elements[i][j] != BLANK ||
        (state.elements[i - 1][j] != opp && state.elements[i + 1][j] != opp && state.elements[i][j - 1] != opp &&
         state.elements[i][j + 1] != opp && state.elements[i - 1][j - 1] != opp &&
         state.elements[i + 1][j + 1] != opp && state.elements[i - 1][j + 1] != opp &&
         state.elements[i + 1][j - 1] != opp))
        return -1;
    return 1;
}

/* Make move */
void make_move(state_t *state, char player, int i, int j)
{
    char opp = state->elements[i][j] == BLACK ? WHITE : BLACK;
    if (state->elements[i - 1][j] == opp)
        for (int k = i; state->elements[k][j] != player; k--)
            state->elements[k][j] = player;
    if (state->elements[i + 1][j] == opp)
        for (int k = i; state->elements[k][j] != player; k++)
            state->elements[k][j] = player;
    if (state->elements[i][j - 1] == opp)
        for (int k = j; state->elements[i][k] != player; k--)
            state->elements[i][k] = player;
    if (state->elements[i][j + 1] == opp)
        for (int k = j; state->elements[i][k] != player; k++)
            state->elements[i][k] = player;
    if (state->elements[i + 1][j + 1] == opp)
        for (int k = 1; state->elements[i + k][j + k] != player; k++)
            state->elements[i + k][j + k] = player;
    if (state->elements[i - 1][j - 1] == opp)
        for (int k = 1; state->elements[i - k][j - k] != player; k++)
            state->elements[i - k][j - k] = player;
    if (state->elements[i - 1][j + 1] == opp)
        for (int k = 1; state->elements[i - k][j + k] != player; k++)
            state->elements[i - k][j + k] = player;
    if (state->elements[i + 1][j - 1] == opp)
        for (int k = 1; state->elements[i + k][j - k] != player; k++)
            state->elements[i + k][j - k] = player;
}

/* Minimax algorithm */
state_t *minimax_decision(state_t *init_state)
{
    if (is_terminal(*init_state) == 1)
    {
        utility(*init_state, &init_state->minmax_val[0] , NULL);
        return init_state;
    } else
    {
        fill_childs(init_state);
        int val[2];
        state_t *action_state;
        action_state = init_state->childs[0];
        minimax_decision(init_state->childs[0]);
        val[0] = init_state->childs[0]->minmax_val;
        for (int i = 1; init_state->childs[i] != NULL; i++)
        {
            minimax_decision(init_state->childs[i]);
            if (init_state->player == BLACK)
            {
                if (init_state->childs[i]->minmax_val > val)
                {
                    val[0] = init_state->childs[i]->minmax_val[0];
                    action_state = init_state->childs[i];
                }
            } else if (init_state->player == WHITE)
                if (init_state->childs[i]->minmax_val < val)
                {
                    val[0] = init_state->childs[i]->minmax_val;
                    action_state = init_state->childs[i];
                }
        }
        init_state->minmax_val[0] = val[0];
        init_state->minmax_val[1] = val[1];
        return action_state;
    }
}

/* Initialization the board */
void init_board(state_t *state)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            state->elements[i][j] = '.';
    state->elements[3][3] = WHITE;
    state->elements[3][4] = BLACK;
    state->elements[4][3] = BLACK;
    state->elements[4][4] = WHITE;
}

int main()
{
    int x, y;
    state_t init_state = {
            .childs = {NULL},
            .player = BLACK,
    };
    printf("\t\'O\': White\t\'@\': Black\t\'.\': Empty\n");
    init_board(&init_state);
    print_state(init_state);
    printf("Your turn (x,y): ");
    scanf("%d %d", &x, &y);
    return 0;
}
