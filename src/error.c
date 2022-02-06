#include "../inc/error.h"

void throwError(const char* desc, const char* fname, int line, int col) {
    fprintf(stderr, "Error: (%s: %d/%d) -> %s\n", fname, line, col, desc);
}