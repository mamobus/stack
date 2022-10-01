#include "stack_functions.h"

int main()
{
    stack_t *stack1 = stack_new();

    stack1->log_file = fopen("log.txt", "w");

    for(size_t i = 0; i < 1000; i++)
    {
        stack_push(stack1, i);
    }

    for(size_t i = 0; i < 1000; i++)
    {
        printf("%lg ", stack_pop(stack1));
    }

    stack_del(stack1);

    return 0;   
}