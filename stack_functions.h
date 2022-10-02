#ifndef STACK_FUNCTIONS_H
#define STACK_FUNCTIONS_H

#define POISON 13
#define DETECTOR 69420993

typedef int STACK_TYPE;
typedef long HASH_TYPE;

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

// enum errors_t
// {
//     sda = 1,
//     deas =2,
// };

struct stack_t
{
    STACK_TYPE *data = nullptr;
    size_t size     = 0;
    size_t capacity = 0;
    FILE *log_file = nullptr;

    size_t hash = 0; 
    // enum errors_t error; 
};

stack_t *stack_new();

void stack_push(stack_t *stack, STACK_TYPE num);

STACK_TYPE stack_pop(stack_t *stack);

void stack_del(stack_t *stack);

void stack_dump(stack_t *stack, const char *file_name, int line);

void stack_check(stack_t *stack);

size_t get_data_hash(stack_t *stack);

size_t get_hash(HASH_TYPE num);

#endif //STACK_FUNCTIONS_H