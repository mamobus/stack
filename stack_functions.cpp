#define POISON 13
#define DETECTOR 14

#include "stack_functions.h" //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM

stack_t *stack_new()
{
    stack_t *stack = (stack_t*)calloc(1, sizeof(stack_t));

    assert(stack != nullptr);

    stack_dump(stack, __FUNCTION__, __LINE__);

    return stack;
}

void stack_push(stack_t *stack, double num)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    if(stack->capacity == 0)
    {
        stack->capacity = 1; //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM
        stack->data = (double*)calloc(3, sizeof(double));
        assert(stack->data != nullptr);

        stack->data[0] = DETECTOR;
        stack->data[1] = DETECTOR;
    }  

    stack_check(stack);

    if(stack->size == stack->capacity) //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM
    {
        stack->capacity = stack->capacity * 2;  //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM
        stack->data = (double*)realloc(stack->data, (stack->capacity + 2) * sizeof(double));
        assert(stack->data != nullptr); 
    }
    
    stack->data[stack->size + 1] = num;
    stack->data[stack->size + 2] = DETECTOR;
    stack->size++;

    stack_dump(stack, __FUNCTION__, __LINE__);
}

double stack_pop(stack_t *stack)
{
    stack_dump(stack, __FUNCTION__, __LINE__);
    
    stack_check(stack);

    double temp = 0;
    
    if(stack->size <= stack->capacity / 4)
    {
        stack->capacity = stack->capacity / 2;
        stack->data = (double*)realloc(stack->data, (stack->capacity + 2) * sizeof(double*));
        assert(stack->data != nullptr);
    }

    temp = stack->data[stack->size];

    stack->data[stack->size] = DETECTOR;
    stack->data[stack->size + 1] = POISON;   

    stack->size--;

    stack_dump(stack, __FUNCTION__, __LINE__);

    return temp;
}

void stack_del(stack_t *stack)
{
    // stack_dump(stack);

    for(size_t i = 0; i < stack->size; i++)
    {
        stack->data[i] = POISON;
    }

    free(stack->data);
    free(stack->log_file);
    free(stack);
}

void stack_dump(stack_t *stack, const char *func_name, int line)
{
    // printf(                  "In func % 11s, line %03d\nsize = %zu, capacity = %zu\n\n", func_name, line, stack->size, stack->capacity);
    // fprintf(stack->log_file, "In func % 11s, line %03d\nsize = %zu, capacity = %zu\n\n", func_name, line, stack->size, stack->capacity);
}



void stack_check(stack_t *stack)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    assert(stack->data[0] == DETECTOR);
    assert(stack->data[stack->size + 1] == DETECTOR);
    assert(stack != nullptr);
    assert(stack->data != nullptr); 
    assert(stack->size >= 0);
    assert(stack->size <= stack->capacity);
}

size_t gethash(double *data, size_t size)
{
        
}

/** что нужно сделать:
 * в начале и в конце даты канарейка и проверять не тронули ли их DETECTOR
 * в удалении заливать нелогичные значения
 * calloc вместо malloc
 * проверять размеры
 * динамическое изменение размера
 * логи
 * удалять сам стэк и его дату
 * HASH
 * 
 */
