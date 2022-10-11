#include "stack_functions.h"
#include <time.h>

int main()
{
    printf("aa\n");

    clock_t start = clock();

    printf("aa\n");
    
    stack_t *stack1 = stack_new();

    printf("aa\n");
    
    stack1->log_file = fopen("log.txt", "w");

    printf("aa\n");

    fprintf(stack1->log_file, "\n");

    for(size_t i = 0; i < 10; i++)
    {
        stack_push(stack1, i);
        // if(i % 8 == 0)
        // {
        //     stack1->data[i] = 777;
        // }
    }

    assert(stack1->error == 0);

    clock_t finish = clock();

    printf("\nTIME SPENT = %ld\n", finish - start);
  
    for(size_t i = 0; i < 10; i++)
    {
        printf("%d ", stack_pop(stack1));
    }

    stack_del(stack1);

    return 0;   
}