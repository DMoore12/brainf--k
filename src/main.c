#include "../inc/main.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        throwError("no args given", "__init", -1, -1);

        return EXIT_FAILURE;
    }

    buildQueue(argv[1]);

    return EXIT_SUCCESS;
}