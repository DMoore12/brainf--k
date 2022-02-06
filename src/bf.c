#include "../inc/bf.h"

static int insertNode(list_t* list, char op);
static void listWalk(list_t* list, const char* desc);
static void memset(void* arr, unsigned char val, size_t len);

list_t* buildQueue(const char* fname) {
    list_t* list = malloc(sizeof(list_t));
    FILE* fptr = fopen(fname, "r");
    int ret = 0;

    list->head = NULL;

    if (list == NULL) {
        throwError("could not alloc (root)", "bf.c", 12, -1);
        
        return NULL;
    }

    if (fptr == NULL) {
        throwError("could not open", fname, -1, -1);

        return NULL;
    }

    do {
        ret = fgetc(fptr);
        if (ret != EOF) {
            fseek(fptr, 1, SEEK_CUR);
            if (!insertNode(list, ret)) {
                throwError("could not alloc (node)", "bf.c", 28, -1);
                fclose(fptr);

                return NULL;
            }
        }
    } while (ret != EOF);

    return list;
}

int queueInterpret(list_t* list) {
    instruction_t* inst = list->head;
    int* bins = malloc(sizeof(int) * 30000);
    int* bin_curr;
    list_t next;
    char in;

    listWalk(list, "before");

    if (bins == NULL) {
        throwError("could not alloc (bins)", "bf.c", 46, -1);

        return 0;
    }

    bin_curr = bins;

    while (inst != NULL) {
        printf("%c", inst->op);
        // switch (inst->op) {
        //     case OP_LB:
        //     {
        //         next.head = inst->next_ptr;
        //         if (!queueInterpret(&next)) {
        //             throwError("queueInterpret failed in nest", "bf.c", 63, -1);

        //             return 0;
        //         }

        //         break;
        //     }
        //     case OP_RB:
        //     {
        //         return 1;
        //     }
        //     case OP_LEFT:
        //     {
        //         --bin_curr;

        //         break;
        //     }
        //     case OP_RIGHT:
        //     {
        //         ++bin_curr;

        //         break;
        //     }
        //     case OP_PLUS:
        //     {
        //         ++(*bin_curr);

        //         break;
        //     }
        //     case OP_MINUS:
        //     {
        //         --(*bin_curr);

        //         break;
        //     }
        //     case OP_OUT:
        //     {
        //         printf("%d", *bin_curr);

        //         break;
        //     }
        //     case OP_IN:
        //     {
        //         fgets(&in, 1, stdin);
        //         *bin_curr = in;

        //         break;
        //     }
        // }

        inst = inst->next_ptr;
    }

    return 1;
}

static int insertNode(list_t* list, char op) {
    instruction_t* inst;

    inst = malloc(sizeof(inst));

    if (inst == NULL) {
        throwError("could not alloc (node)", "bf.c", 56, -1);

        return 0;
    }

    inst->op = op;
    if (list->head == NULL) {
        list->head = inst;
        list->tail = inst;
    } else {
        inst->last_ptr = list->tail;
        inst->next_ptr = NULL;
        list->tail->next_ptr = inst;
        list->tail = inst;
    }
    
    return 1;
}

static void listWalk(list_t* list, const char* desc) {
    instruction_t* inst = list->head;

    printf("Debug: %s\n", desc);

    while (inst != NULL) {
        printf("%c", inst->op);
        inst = inst->next_ptr;
    }

    printf("\n\n");
}

static void memset(void* arr, unsigned char val, size_t len) {
    size_t i;
    unsigned char* dest = arr;

    for (i = 0; i < len; i++) {
        dest[i] = val;
    }
}
