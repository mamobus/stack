#include "stack_functions.h"
#include <time.h>

int main()
{
    clock_t start = clock();

    stack_t *stack1 = stack_new();

    stack1->log_file = fopen("log.txt", "w");

    fprintf(stack1->log_file, "\n");

    for(size_t i = 0; i < 1000; i++)
    {
        stack_push(stack1, i);
        // if(i % 80 == 0)
        // {
        //     stack1->data[15] = 777;
        // }
    }

    clock_t finish = clock();

    printf("\nTIME SPENT = %ld\n", finish - start);
  
    for(size_t i = 0; i < 1000; i++)
    {
        printf("%d ", stack_pop(stack1));
    }

    stack_del(stack1);

    return 0;   
}