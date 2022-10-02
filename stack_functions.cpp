#include "stack_functions.h" //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM

stack_t *stack_new()
{
    stack_t *stack = (stack_t*)calloc(1, sizeof(stack_t));

    assert(stack != nullptr);

    stack_dump(stack, __FUNCTION__, __LINE__);

    return stack;
}

void stack_push(stack_t *stack, STACK_TYPE num)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    if(stack->capacity == 0)
    {
        stack->capacity = 1; //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM
        stack->data = (STACK_TYPE*)calloc(3, sizeof(STACK_TYPE));
        assert(stack->data != nullptr);

        stack->data[0] = DETECTOR;
        stack->data[1] = DETECTOR;
    }  

    stack_check(stack);

    if(stack->size == stack->capacity) //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM
    {
        stack->capacity = stack->capacity * 2;  //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM
        stack->data = (STACK_TYPE*)realloc(stack->data, (stack->capacity + 2) * sizeof(STACK_TYPE));
        assert(stack->data != nullptr); 
    }

    assert(stack->hash == get_data_hash(stack));    

    stack->data[stack->size + 1] = num;
    stack->data[stack->size + 2] = DETECTOR;

    stack->size++;

    stack->hash += get_hash((HASH_TYPE) stack->data[stack->size]);
    // stack->hash = get_data_hash(stack);

    stack_dump(stack, __FUNCTION__, __LINE__);
}

STACK_TYPE stack_pop(stack_t *stack)
{
    stack_dump(stack, __FUNCTION__, __LINE__);
    
    stack_check(stack);

    STACK_TYPE temp = 0;
    
    if(stack->size <= stack->capacity / 4)
    {
        stack->capacity = stack->capacity / 2;
        stack->data = (STACK_TYPE*)realloc(stack->data, (stack->capacity + 2) * sizeof(STACK_TYPE));
        assert(stack->data != nullptr);
    }

    temp = stack->data[stack->size];

    stack->data[stack->size] = DETECTOR;
    stack->data[stack->size + 1] = POISON;   

    stack->size--;

    stack_dump(stack, __FUNCTION__, __LINE__);

    return temp;
}

void stack_dump(stack_t *stack, const char *func_name, int line) //ПОЧЕМУ НЕ ВЫВОДИТ STACK_NEW В ФАЙЛ
{
    // printf(                  "In func %s, line %d\nsize = %zu, capacity = %zu\n", func_name, line, stack->size, stack->capacity);
    fprintf(stack->log_file, "In func %s, line %d\nsize = %zu, capacity = %zu\n", func_name, line, stack->size, stack->capacity);

    if(stack->data != nullptr)
    {
        for(size_t i = 0; i < stack->size + 2; i++)
        {
            // printf("%d ", stack->data[i]);
            fprintf(stack->log_file, "%d ", stack->data[i]);
        }
        // printf("\nhash = %zu\n\n", stack->hash);
        fprintf(stack->log_file, "\nhash = %zu\n\n", stack->hash);
    }
    else 
    {
        // printf("\ndata = nullptr\n\n");
        fprintf(stack->log_file, "\ndata = nullptr\n\n");
    }
}



void stack_check(stack_t *stack)
{
    // stack_dump(stack, __FUNCTION__, __LINE__);

    assert(stack->data[0] == DETECTOR);
    assert(stack->data[stack->size + 1] == DETECTOR);
    assert(stack != nullptr);
    assert(stack->data != nullptr); 
    assert(stack->size >= 0);
    assert(stack->size <= stack->capacity);
}

size_t get_data_hash(stack_t *stack) //ALARMALARMALARMALARMALARMALARMALARMALARMALARMALARMALARM а не будет быстрее просто складывать в 16 байтовое? 
{
    size_t hash = 0;

    for(size_t i = 1; i < stack->size + 1; i++)
    {
        for(size_t j = 0; j < 8 * sizeof(HASH_TYPE); j++)
        {
            hash += (((HASH_TYPE)stack->data[i] & (1 << j)) >> j);
        }
    }
    
    return hash;
}

size_t get_hash(HASH_TYPE num)
{
    size_t hash = 0;

    for(size_t i = 0; i < 8  * sizeof(HASH_TYPE); i++)
    {
        hash += (num & (1 << i)) >> i;
    }

    return hash;
}

void stack_del(stack_t *stack)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    for(size_t i = 0; i < stack->size + 2; i++)
    {
        stack->data[i] = POISON;
    }

    free(stack->data);
    free(stack->log_file);
    free(stack);
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
