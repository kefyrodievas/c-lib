#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct _vector{
    void * data;
    ssize_t data_size;
    ssize_t length;
    ssize_t size;
} _vector;

_vector new_vector(ssize_t data_size){
    _vector ret;
    ret.data_size = data_size;
    ret.size = 10;
    ret.length = 0;
    ret.data = malloc(ret.data_size * ret.size);
}




#endif