#include "../inc/bf.h"

static void binDump(int* bins, size_t size, int ptr, int instance, char op);
static instruction_t* skipLoop(instruction_t* inst);
static char removeNode(list_t* list);
static int insertNode(list_t* list, char op);
static void listWalk(list_t* list, const char* desc);
static void memset(void* arr, unsigned char val, size_t len);

list_t* buildQueue(const char* fname) {
    list_t* list = malloc(sizeof(list_t));
    FILE* fptr = fopen(fname, "r");
    int ret = 0;

    list->head = NULL;

    if (list == NULL) {
        throwError("could not alloc (root)", "bf.c", 17, -1);
        
        return NULL;
    }

    if (fptr == NULL) {
        throwError("could not open", fname, -1, -1);

        return NULL;
    }

    do {
        ret = fgetc(fptr);
        if (ret != EOF) {
            if (!insertNode(list, ret)) {
                throwError("could not alloc (node)", "bf.c", 32, -1);
                fclose(fptr);

                return NULL;
            }
        }
    } while (ret != EOF);

    fclose(fptr);

    return list;
}

int syntaxCheck(list_t* list) {
    int bcnt = 0;
    int err_left = 0;
    instruction_t* inst = list->head;

    while (inst != NULL) {
        if (inst->op == OP_LB) {
            ++bcnt;
        } else if (inst->op == OP_RB) {
            --bcnt;
        }

        if (bcnt < 0) {
            err_left = 1;
        }

        inst = inst->next_ptr;
    }

    if (bcnt || err_left) {
        if (bcnt > 0) {
            throwError("lacking ']' for op '['", "bf.c", 61, -1);
        } else {
            throwError("excess ']' given", "bf.c", 63, -1);
        }
    }

    return (bcnt == 0) ? 1 : 0;
}

int queueInterpret(list_t* list, int* ptr) {
    int* bins;
    instruction_t* inst = list->head;
    list_t nl;
    static int* bin_curr;
    static int running;
    static int instance;
    char in;
    char op;

    nl.tail = list->tail;

    if (!running) {
        bins = malloc(sizeof(int) * 30000);
        
        if (bins == NULL) {
            throwError("could not alloc (bins)", "bf.c", 53, -1);

            return 0;
        }

        memset(bins, 0, sizeof(int) * 30000);

        bin_curr = bins;
        running = 1;
    } else {
        bins = ptr;
        running++;
    }

    while (inst != NULL) {
        // binDump(bins, 3, bin_curr - bins, instance, inst->op);
        switch (inst->op) {
            case OP_LB:
            {
                nl.head = inst->next_ptr;
                while (*bin_curr) {
                    ++instance;
                    if (!queueInterpret(&nl, bins)) {
                        throwError("queueInterpret failed in nest", "bf.c", 76, -1);

                        return 0;
                    }
                }

                inst = skipLoop(inst);

                break;
            }
            case OP_RB:
            {
                --instance;

                return 1;
            }
            case OP_LEFT:
            {
                --bin_curr;

                break;
            }
            case OP_RIGHT:
            {
                ++bin_curr;

                break;
            }
            case OP_PLUS:
            {
                ++(*bin_curr);

                break;
            }
            case OP_MINUS:
            {
                --(*bin_curr);

                break;
            }
            case OP_OUT:
            {
                printf("%c", *bin_curr);

                break;
            }
            case OP_IN:
            {
                fgets(&in, 1, stdin);
                *bin_curr = in;

                break;
            }
        }
        inst = inst->next_ptr;
    }

    return 1;
}

static void binDump(int* bins, size_t size, int ptr, int instance, char op) {
    size_t i;
    static int iter;

    printf("(%d:%d)%5d %c:", ptr, instance, iter++, op);

    for (i = 0; i < size; i++) {
        printf(" %2d", bins[i]);
    }

    printf("\n");
}

static instruction_t* skipLoop(instruction_t* inst) {
    while (inst->op != OP_RB) {
        inst = inst->next_ptr;
    }

    return inst;
}

static char removeNode(list_t* list) {
    char ret;
    instruction_t* nh = list->head;

    ret = nh->op;
    
    if (nh->next_ptr == NULL) {
        list->head = NULL;
        list->tail = NULL;
        free(nh);
    } else {
        list->head = nh->next_ptr;
        free(nh);
    }

    return ret;
}

static int insertNode(list_t* list, char op) {
    instruction_t* inst;

    inst = malloc(sizeof(inst));

    if (inst == NULL) {
        throwError("could not alloc (node)", "bf.c", 170, -1);

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
}

static void memset(void* arr, unsigned char val, size_t len) {
    size_t i;
    unsigned char* dest = arr;

    for (i = 0; i < len; i++) {
        dest[i] = val;
    }
}
