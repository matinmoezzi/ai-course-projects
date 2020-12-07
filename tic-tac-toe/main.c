#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct state
{
    char player, elements[3][3];
    int minimax_val;
    struct state *parent, *childs[9];
};
typedef struct state state_t;

/* Test a state is terminal or not */
/* return 1 if it is a terminal node otherwise -1 */
int is_terminal(state_t state)
{
    int ret_val = 1;
    for (int i = 0; i < 3; i++)
    {
        if (state.elements[i][0] == state.elements[i][1] && state.elements[i][1] == state.elements[i][2])
            return 1;
        if (state.elements[0][i] == state.elements[1][i] && state.elements[1][i] == state.elements[2][i])
            return 1;
        for (int j = 0; j < 3; j++)
            if (state.elements[i][j] != 'X' && state.elements[i][j] != 'O')
                ret_val = -1;
    }
    if (state.elements[0][0] == state.elements[1][1] && state.elements[1][1] == state.elements[2][2])
        return 1;
    if (state.elements[0][2] == state.elements[1][1] && state.elements[1][1] == state.elements[2][0])
        return 1;
    return ret_val;
}

/* Evaluate utility unit of a terminal node */
/* 1 for X win, -1 for O win and 0 for draw */
int utility(state_t state)
{
    for (int i = 0; i < 3; i++)
        if (state.elements[i][0] == 'X' && state.elements[i][1] == 'X' && state.elements[i][2] == 'X')
            return 1;
        else if (state.elements[i][0] == 'O' && state.elements[i][1] == 'O' && state.elements[i][2] == 'O')
            return -1;
    for (int i = 0; i < 3; i++)
        if (state.elements[0][i] == 'X' && state.elements[1][i] == 'X' && state.elements[2][i] == 'X')
            return 1;
        else if (state.elements[0][i] == 'O' && state.elements[1][i] == 'O' && state.elements[2][i] == 'O')
            return -1;
    if (state.elements[0][0] == 'X' && state.elements[1][1] == 'X' && state.elements[2][2] == 'X')
        return 1;
    if (state.elements[0][0] == 'O' && state.elements[1][1] == 'O' && state.elements[2][2] == 'O')
        return -1;
    if (state.elements[0][2] == 'X' && state.elements[1][1] == 'X' && state.elements[2][0] == 'X')
        return 1;
    if (state.elements[0][2] == 'O' && state.elements[1][1] == 'O' && state.elements[2][0] == 'O')
        return -1;
    return 0;
}

/* Copy two state elements */
void copy_state(state_t *src, state_t *dest)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            dest->elements[i][j] = src->elements[i][j];
}

/* Fill childs of a state */
void fill_childs(state_t *state)
{
    int n = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state->elements[i][j] != 'X' && state->elements[i][j] != 'O')
            {
                state->childs[n] = (state_t *) malloc(sizeof(state_t));
                state->childs[n]->parent = state;
                copy_state(state, state->childs[n]);
                state->childs[n]->elements[i][j] = state->player;
                state->childs[n]->player = state->player == 'X' ? 'O' : 'X';
                n++;
            }
}

/* Minimax algorithm with alpha-beta pruning */
state_t *minimax_decision_pruning(state_t *init_state, int alpha, int beta)
{
    if (is_terminal(*init_state) == 1)
    {
        init_state->minimax_val = utility(*init_state);
        return init_state;
    } else
    {
        fill_childs(init_state);
        int val, new_alpha = alpha, new_beta = beta;
        state_t *action_state;
        action_state = init_state->childs[0];
        minimax_decision_pruning(init_state->childs[0], alpha, beta);
        val = init_state->childs[0]->minimax_val;
        if (init_state->player == 'X' && val < new_beta)
            new_beta = val;
        if (init_state->player == 'O' && val > new_alpha)
            new_alpha = val;
        if ((init_state->player == 'X' && val <= beta) || (init_state->player == 'O' && val >= alpha))
            for (int i = 1; init_state->childs[i] != NULL; i++)
            {
                minimax_decision_pruning(init_state->childs[i], new_alpha, new_beta);
                if (init_state->player == 'X')
                {
                    if (init_state->childs[i]->minimax_val > beta)
                        break;
                    if (init_state->childs[i]->minimax_val > val)
                    {
                        val = init_state->childs[i]->minimax_val;
                        action_state = init_state->childs[i];
                    }
                    if (val < new_beta)
                        new_beta = val;
                } else if (init_state->player == 'O')
                {
                    if (init_state->childs[i]->minimax_val < alpha)
                        break;
                    if (init_state->childs[i]->minimax_val < val)
                    {
                        val = init_state->childs[i]->minimax_val;
                        action_state = init_state->childs[i];
                    }
                    if (val > new_alpha)
                        new_alpha = val;
                }
            }
        init_state->minimax_val = val;
        return action_state;
    }
}

/* Minimax algorithm */
state_t *minimax_decision(state_t *init_state)
{
    if (is_terminal(*init_state) == 1)
    {
        init_state->minimax_val = utility(*init_state);
        return init_state;
    } else
    {
        fill_childs(init_state);
        int val;
        state_t *action_state;
        action_state = init_state->childs[0];
        minimax_decision(init_state->childs[0]);
        val = init_state->childs[0]->minimax_val;
        for (int i = 1; init_state->childs[i] != NULL; i++)
        {
            minimax_decision(init_state->childs[i]);
            if (init_state->player == 'X')
            {
                if (init_state->childs[i]->minimax_val > val)
                {
                    val = init_state->childs[i]->minimax_val;
                    action_state = init_state->childs[i];
                }
            } else if (init_state->player == 'O')
                if (init_state->childs[i]->minimax_val < val)
                {
                    val = init_state->childs[i]->minimax_val;
                    action_state = init_state->childs[i];
                }
        }
        init_state->minimax_val = val;
        return action_state;
    }
}

/* Print a state */
void print_state(state_t state)
{
    for (int i = 0; i < 3; i++)
    {
        if (state.elements[i][0] == 'O')
            printf("\033[1;31m");
        else if (state.elements[i][0] == 'X')
            printf("\033[1;34m");
        printf("\t%c\t", state.elements[i][0]);
        printf("\033[0m");
        for (int j = 1; j < 3; j++)
        {
            if (state.elements[i][j] == 'O')
                printf("\033[1;32m|\t\033[1;31mO\033[0m\t");
            else if (state.elements[i][j] == 'X')
                printf("\033[1;32m|\t\033[1;34mX\033[0m\t");
            else
                printf("\033[1;32m|\033[0m\t%c\t", state.elements[i][j]);
        }
        if (i != 2)
            printf("\n  \033[1;32m---------------------\033[0m  \n");
    }
    printf("\n");
}

/* Update a state */
int update_state(state_t *state, int pos, char player)
{
    int i = (int) ceil(pos / 3.0) - 1, j = (pos - 1) % 3;
    if (state->elements[i][j] == 'X' || state->elements[i][j] == 'O')
        return -1;
    state->elements[i][j] = player;
    return 0;
}

int main()
{
    char c;
    state_t *action, init_state = {
            .elements = {{'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'}},
            .player = 'X',
            .childs = {NULL},
            .parent = NULL
    };
    printf("You: \033[1;31mO\033[0m\tCom: \033[1;34mX\033[0m\n");
    print_state(init_state);
    while (1)
    {
        printf("\033[1;31mYour Turn O\033[0m (box number): ");
        if ((c = (char) getchar()) == '\n') c = (char) getchar();
        if (update_state(&init_state, c - '0', 'O') == -1)
        {
            fprintf(stderr, "Invalid number.\n");
            return EXIT_FAILURE;
        }
        print_state(init_state);
        if (is_terminal(init_state) == 1)
        {
            printf("\033[;35mYou win.\033[0m\n");
            return 0;
        }
        clock_t begin = clock(), end;
        action = minimax_decision(&init_state);
        //action = minimax_decision_pruning(&init_state, -2, 2);
        end = clock();
        printf("elapsed time: %g\n", ((double) (end - begin)) / CLOCKS_PER_SEC);
        printf("\033[1;34mComputer Turn X:\033[0m\n");
        print_state(*action);
        if (is_terminal(*action) == 1)
        {
            switch (action->minimax_val)
            {
                case 1:
                    printf("\033[1;35mYou lose.\033[0m\n");
                    break;
                case -1:
                    printf("\033[;35mYou win.\033[0m\n");
                    break;
                case 0:
                    printf("\033[1;35mDraw.\033[0m\n");
                    break;
            }
            return 0;
        }
        copy_state(action, &init_state);
    }
}
