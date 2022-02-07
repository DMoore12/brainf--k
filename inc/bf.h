#ifndef _BF_H_
#define _BF_H_

// Includes
#include "stdlib.h"
#include "stdarg.h"
#include "../inc/error.h"

// Structs, enums, etc
enum {
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_RB = ']',
    OP_LB = '[',
    OP_RIGHT = '>',
    OP_LEFT = '<',
    OP_OUT = '.',
    OP_IN = ','
};

typedef struct inst_t {
    char           op;

    struct inst_t *next_ptr;
    struct inst_t *last_ptr;
} instruction_t;

typedef struct {
    instruction_t *head;
    instruction_t *tail;
} list_t;

// Prototypes
list_t* buildQueue(const char* fname);
int syntaxCheck(list_t* list);
int queueInterpret(list_t* list, int* ptr);

#endif