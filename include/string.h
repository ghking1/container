#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t index_KMP(const char*, const char*, size_t);
size_t index_BM(const char*, const char*, size_t);
size_t BKDRHash(char *);

#endif
