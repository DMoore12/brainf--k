#include "../inc/main.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        throwError("no args given", "__init", -1, -1);

        return EXIT_FAILURE;
    }

    list_t* list = buildQueue(argv[1]);
    queueInterpret(list, NULL);

    return EXIT_SUCCESS;
}