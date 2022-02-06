#ifndef _BF_H_
#define _BF_H_

// Includes
#include "stdlib.h"
#include "../inc/error.h"

// Structs, enums, etc
typedef enum {
    OP_PLUS,
    OP_MINUS,
    OP_RB,
    OP_LB,
    OP_RIGHT,
    OP_LEFT
} OP_t;

typedef struct inst_t {
    struct isnt_t *next_ptr;
    struct inst_t *last_ptr;
    OP_t           op;
} instruction_t;

typedef struct {
    instruction_t *head;
    instruction_t *tail;
} list_t;

// Prototypes
list_t* buildQueue(const char* fname);

#endif