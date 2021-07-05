#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack_t
{
    int row;
    int col;
    int value;
    struct stack_t *next;

} stack;

stack* create_node(int row, int col, int value)
{
    stack *_ = (stack*)malloc(sizeof(stack));

    _->row = row;
    _->col = col;
    _->value = value;
    _->next = NULL;

    return _;
}

void push(stack *element, stack **stk)
{
    stack *cur = *stk;

    *stk = element;
    element->next = cur;
}

stack* pop(stack **stk)
{
    stack *cur = *stk;
    
    *stk = cur->next;
    cur->next = NULL;
    return cur;
}

bool is_it_safe(int (*values)[9], int row, int col, int value)
{
    for (int i = 0; i < 9; i++)
        if (values[i][col] == value)
            return false;

    for (int j = 0; j < 9; j++)
        if (values[row][j] == value)
            return false;

    int p = row - row % 3;
    int q = col - col % 3;
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (values[p + i][q + j] == value)
                return false;

    return true;
}

void solve(int (*values)[9])
{
    int l = 1, i, j, k;
    stack *stk = NULL, *tmp = NULL;

    up:

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (values[i][j] == 0)
            {
                for (k = l; k <= 9; k++)
                {
                    if (is_it_safe(values, i, j, k))
                    {
                        values[i][j] = k;
                        push(create_node(i, j, values[i][j]), &stk);
                        l = 1;
                        goto down;
                    }
                }

                tmp = pop(&stk);

                if (tmp != NULL)
                {
                    values[tmp->row][tmp->col] = 0;
                    l = tmp->value + 1;
                    free(tmp);
                    
                    while (l == 10)
                    {
                        tmp = pop(&stk);
                        values[tmp->row][tmp->col] = 0;
                        l = tmp->value + 1;
                        free(tmp);
                    }

                    goto up;
                }
                else
                {
                    exit(1);
                }
            }

            down:
        }
    }
}

int main()
{
    int values[9][9];

    printf("Enter the sudoku board\n");

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            scanf("%d", &values[i][j]);

    solve(values);

    printf("Result\n");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", values[i][j]);

        printf("\n");
    }

    return 0;
}
