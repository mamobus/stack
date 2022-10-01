#ifndef STACK_FUNCTIONS_H
#define STACK_FUNCTIONS_H

// #define POISON = 13;

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

enum errors_t
{
    sda = 1,
    deas =2,
};

struct stack_t
{
    double *data = nullptr;
    size_t size     = 0;
    size_t capacity = 0;
    FILE *log_file;

    size_t hash; 
    enum errors_t error; 
};

stack_t *stack_new();

void stack_push(stack_t *stack, double num);

double stack_pop(stack_t *stack);

void stack_del(stack_t *stack);

void stack_dump(stack_t *stack, const char *file_name, int line);

void stack_check(stack_t *stack);

#endif //STACK_FUNCTIONS_H