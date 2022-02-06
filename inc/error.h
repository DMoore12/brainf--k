#ifndef _ERROR_H_
#define _ERROR_H_

// Includes
#include "stdlib.h"
#include "stdio.h"

// Prototypes
void throwError(const char* desc, const char* fname, int line, int col);

#endif