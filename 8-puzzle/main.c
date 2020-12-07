#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BLANK 0                                     // Blank block in 8-puzzle

struct state_t
{
    int h;                                                    // heuristic function
    int g;                                                    // cost function
    unsigned int puzzle[3][3];                                // 8-puzzle
    struct state_t *parent, *left, *right, *up, *down;        // parent and successors of state
};
typedef struct state_t state_t;

struct queue_t
{
    state_t *node;
    struct queue_t *next;
};
typedef struct queue_t queue_t;


/* Print the puzzle */
void print_puzzle(unsigned int puzzle[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%d ", puzzle[i][j]);
        printf("\n");
    }
}

/* Generate random 8-puzzle of initial state */
state_t *generate_random_initial_state()
{
    state_t *init = (state_t *) malloc(sizeof(state_t));
    init->parent = NULL;
    init->g = 0;

    /* Fill the puzzle with number 1 to 8 with blank */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            init->puzzle[i][j] = 3 * i + j + 1;
    init->puzzle[2][2] = BLANK;

    /* Shuffle the puzzle */
    srand(time(0));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int rand_i = rand() % 3, rand_j = rand() % 3;
            unsigned int tmp = init->puzzle[i][j];
            init->puzzle[i][j] = init->puzzle[rand_i][rand_j];
            init->puzzle[rand_i][rand_j] = tmp;
        }
    return init;
}

/* Copy the two puzzle */
void copy_puzzle(unsigned int *dest, const unsigned int *src)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            dest[3 * i + j] = src[3 * i + j];
}

/* Is equal two state */
int equal_state(state_t *s1, state_t *s2)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (s1->puzzle[i][j] != s2->puzzle[i][j])
                return -1;
    return 0;
}

/* Is state the goal */
int test_goal(state_t *state)
{
    unsigned int goal[3][3] = {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 0}};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state->puzzle[i][j] != goal[i][j])
                return -1;
    return 0;
}

/* Expand state */
void expand(state_t *state)
{
    /* Find the blank indexes */
    unsigned int blank_i, blank_j;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state->puzzle[i][j] == BLANK)
            {
                blank_i = i;
                blank_j = j;
            }
    if (blank_j == 0)
    {
        state->right = (state_t *) malloc(sizeof(state_t));
        copy_puzzle((unsigned int *) state->right->puzzle, (unsigned int *) state->puzzle);
        state->right->puzzle[blank_i][blank_j] = state->right->puzzle[blank_i][blank_j + 1];
        state->right->puzzle[blank_i][blank_j + 1] = BLANK;
        if (blank_i == 0)
        {
            state->down = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->down->puzzle, (unsigned int *) state->puzzle);
            state->down->puzzle[blank_i][blank_j] = state->down->puzzle[blank_i + 1][blank_j];
            state->down->puzzle[blank_i + 1][blank_j] = BLANK;
        }
        if (blank_i == 2)
        {
            state->up = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->up->puzzle, (unsigned int *) state->puzzle);
            state->up->puzzle[blank_i][blank_j] = state->up->puzzle[blank_i - 1][blank_j];
            state->up->puzzle[blank_i - 1][blank_j] = BLANK;
        }
        if (blank_i == 1)
        {
            state->down = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->down->puzzle, (unsigned int *) state->puzzle);
            state->down->puzzle[blank_i][blank_j] = state->down->puzzle[blank_i + 1][blank_j];
            state->down->puzzle[blank_i + 1][blank_j] = BLANK;

            state->up = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->up->puzzle, (unsigned int *) state->puzzle);
            state->up->puzzle[blank_i][blank_j] = state->up->puzzle[blank_i - 1][blank_j];
            state->up->puzzle[blank_i - 1][blank_j] = BLANK;
        }
    } else if (blank_j == 2)
    {
        state->left = (state_t *) malloc(sizeof(state_t));
        copy_puzzle((unsigned int *) state->left->puzzle, (unsigned int *) state->puzzle);
        state->left->puzzle[blank_i][blank_j] = state->left->puzzle[blank_i][blank_j - 1];
        state->left->puzzle[blank_i][blank_j - 1] = BLANK;

        if (blank_i == 0)
        {
            state->down = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->down->puzzle, (unsigned int *) state->puzzle);
            state->down->puzzle[blank_i][blank_j] = state->down->puzzle[blank_i + 1][blank_j];
            state->down->puzzle[blank_i + 1][blank_j] = BLANK;
        }
        if (blank_i == 2)
        {
            state->up = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->up->puzzle, (unsigned int *) state->puzzle);
            state->up->puzzle[blank_i][blank_j] = state->up->puzzle[blank_i - 1][blank_j];
            state->up->puzzle[blank_i - 1][blank_j] = BLANK;
        }
        if (blank_i == 1)
        {
            state->down = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->down->puzzle, (unsigned int *) state->puzzle);
            state->down->puzzle[blank_i][blank_j] = state->down->puzzle[blank_i + 1][blank_j];
            state->down->puzzle[blank_i + 1][blank_j] = BLANK;

            state->up = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->up->puzzle, (unsigned int *) state->puzzle);
            state->up->puzzle[blank_i][blank_j] = state->up->puzzle[blank_i - 1][blank_j];
            state->up->puzzle[blank_i - 1][blank_j] = BLANK;
        }
    } else if (blank_j == 1)
    {
        state->right = (state_t *) malloc(sizeof(state_t));
        copy_puzzle((unsigned int *) state->right->puzzle, (unsigned int *) state->puzzle);
        state->right->puzzle[blank_i][blank_j] = state->right->puzzle[blank_i][blank_j + 1];
        state->right->puzzle[blank_i][blank_j + 1] = BLANK;

        state->left = (state_t *) malloc(sizeof(state_t));
        copy_puzzle((unsigned int *) state->left->puzzle, (unsigned int *) state->puzzle);
        state->left->puzzle[blank_i][blank_j] = state->left->puzzle[blank_i][blank_j - 1];
        state->left->puzzle[blank_i][blank_j - 1] = BLANK;
        if (blank_i == 0)
        {

            state->down = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->down->puzzle, (unsigned int *) state->puzzle);
            state->down->puzzle[blank_i][blank_j] = state->down->puzzle[blank_i + 1][blank_j];
            state->down->puzzle[blank_i + 1][blank_j] = BLANK;
        }
        if (blank_i == 2)
        {
            state->up = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->up->puzzle, (unsigned int *) state->puzzle);
            state->up->puzzle[blank_i][blank_j] = state->up->puzzle[blank_i - 1][blank_j];
            state->up->puzzle[blank_i - 1][blank_j] = BLANK;
        }
        if (blank_i == 1)
        {
            state->up = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->up->puzzle, (unsigned int *) state->puzzle);
            state->up->puzzle[blank_i][blank_j] = state->up->puzzle[blank_i - 1][blank_j];
            state->up->puzzle[blank_i - 1][blank_j] = BLANK;

            state->down = (state_t *) malloc(sizeof(state_t));
            copy_puzzle((unsigned int *) state->down->puzzle, (unsigned int *) state->puzzle);
            state->down->puzzle[blank_i][blank_j] = state->down->puzzle[blank_i + 1][blank_j];
            state->down->puzzle[blank_i + 1][blank_j] = BLANK;
        }
    }
}

/* Misplaced heuristic */
void misplaced_heuristic(state_t *state)
{
    int misplaced = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state->puzzle[i][j] != BLANK && state->puzzle[i][j] != 3 * i + j + 1)
                misplaced++;
    state->h = misplaced;
}

/* Manhattan(city-block) heuristic */
void manhattan_heuristic(state_t *state)
{
    int manhattan = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state->puzzle[i][j] != BLANK)
                manhattan += abs(i + 1 - ceil(state->puzzle[i][j] / 3.0)) +
                             abs(j + 1 - (state->puzzle[i][j] % 3 == 0 ? 3 : state->puzzle[i][j] % 3));
    state->h = manhattan;
}

/* Choose minimum evaluation function of queue */
state_t *min_queue(queue_t *root)
{
    queue_t *min = root, *tmp = root;
    while (tmp != NULL)
    {
        if (tmp->node->h + tmp->node->g < min->node->h + min->node->g)
            min = tmp;
        tmp = tmp->next;
    }
    return min->node;
}

/* Enqueue state to queue */
void enqueue_state(queue_t **root, state_t *state)
{
    queue_t *new = (queue_t *) malloc(sizeof(queue_t));
    new->node = state;
    new->next = *root;
    *root = new;
}

/* Dequeue state */
void dequeue_state(queue_t **root, state_t *state)
{
    queue_t *prev, *tmp = *root;
    if (equal_state(tmp->node, state) == 0)
    {
        *root = tmp->next;
        return;
    }
    while (tmp != NULL && equal_state(tmp->node, state) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
}

/* Queue consist given state */
state_t *exist_queue(queue_t *root, state_t *state)
{
    queue_t *tmp = root;
    while (tmp != NULL)
    {
        if (equal_state(tmp->node, state) == 0)
            return tmp->node;
        tmp = tmp->next;
    }
    return NULL;
}

/* Heuristic function driver */
/* 0 for misplaced, 1 for manhattan */
void heuristic_driver(state_t *state)
{
    misplaced_heuristic(state);
}

int main()
{
    /* Start timer */
    clock_t begin = clock();

    /* Define frontier and explored queue (linked-list) */
    queue_t *frontier = NULL, *explored = NULL;
    state_t *exist_state, *min_state;// *init = generate_random_initial_state();
    state_t *init = (state_t *) malloc(sizeof(state_t));
    init->puzzle[0][0] = 0;
    init->puzzle[0][1] = 1;
    init->puzzle[0][2] = 3;
    init->puzzle[1][0] = 7;
    init->puzzle[1][1] = 2;
    init->puzzle[1][2] = 5;
    init->puzzle[2][0] = 8;
    init->puzzle[2][1] = 4;
    init->puzzle[2][2] = 6;
    heuristic_driver(init);
    printf("Initial state:\n");
    print_puzzle(init->puzzle);

    /* Add init state to frontier queue */
    enqueue_state(&frontier, init);

    while (frontier != NULL)
    {
        min_state = min_queue(frontier);
        //printf("next state:\n");
        //print_puzzle(min_state->puzzle);
        dequeue_state(&frontier, min_state);
        if (test_goal(min_state) == 0)
        {
            clock_t end = clock();
            printf("elapsed time: %g (seconds)\n", (double)(end - begin) / CLOCKS_PER_SEC);
            return 0;
        }
        enqueue_state(&explored, min_state);
        expand(min_state);

        /* Expand for every action of state */
        if (min_state->right != NULL)
        {
            if (exist_queue(explored, min_state->right) == NULL)
            {
                min_state->right->g = min_state->g + 1;
                heuristic_driver(min_state->right);
                if ((exist_state = exist_queue(frontier, min_state->right)) == NULL)
                    enqueue_state(&frontier, min_state->right);
                else if (exist_state->g > min_state->right->g)
                    exist_state->g = min_state->right->g;
            }
        }

        if (min_state->left != NULL)
        {
            if (exist_queue(explored, min_state->left) == NULL)
            {
                min_state->left->g = min_state->g + 1;
                heuristic_driver(min_state->left);
                if ((exist_state = exist_queue(frontier, min_state->left)) == NULL)
                    enqueue_state(&frontier, min_state->left);
                else if (exist_state->g > min_state->left->g)
                    exist_state->g = min_state->left->g;
            }
        }

        if (min_state->up != NULL)
        {
            if (exist_queue(explored, min_state->up) == NULL)
            {
                min_state->up->g = min_state->g + 1;
                heuristic_driver(min_state->up);
                if ((exist_state = exist_queue(frontier, min_state->up)) == NULL)
                    enqueue_state(&frontier, min_state->up);
                else if (exist_state->g > min_state->up->g)
                    exist_state->g = min_state->up->g;
            }
        }

        if (min_state->down != NULL)
        {
            if (exist_queue(explored, min_state->down) == NULL)
            {
                min_state->down->g = min_state->g + 1;
                heuristic_driver(min_state->down);
                if ((exist_state = exist_queue(frontier, min_state->down)) == NULL)
                    enqueue_state(&frontier, min_state->down);
                else if (exist_state->g > min_state->down->g)
                    exist_state->g = min_state->down->g;
            }
        }
    }
    return 0;
}
