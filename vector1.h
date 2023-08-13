#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

struct _vector;

// void _append(struct _vector *vector, void* element);
// void _prepend(struct _vector *vector, void *element);
// void _remove(struct _vector *vector, int pos);
// void _destroy(struct _vector *vector);
// void _reset(struct _vector *vector);

struct vector_t
{
    void *data;
    size_t size;
    size_t dataSize;
    size_t length;
} vector_t;

typedef struct vector_t vector;

vector vec_new(size_t dataSize) {
    vector ret;
    ret.data = malloc(10 * dataSize);
    ret.dataSize = dataSize;
    ret.size = 10;
    ret.length = 0;
    return ret;
}

void append(vector *vec, void* element)
{
    void *new;
    if(vec->length + 1 > vec->size){
        new = malloc(vec->size * 2 * vec->dataSize);
        memcpy(new, vec->data, vec->size * vec->dataSize);
        free(vec->data);
        vec->data = new;
        vec->size *= 2;
    }
    memcpy(vec->data + vec->length, element, vec->dataSize);
    vec->length++;
}

void *at(vector *vec, int pos)
{
    void *data;
    memcpy(data, vec->data + pos, vec->dataSize);
    return data;
}

// void _prepend(struct _vector *vector, void *element)
// {
//     vector->size = vector->length + 1 > vector->size ? vector->size *=2 : vector->size;
//     int *new = (int*)malloc(vector->size * sizeof(int));
//     memcpy(new + 1, vector->data, vector->length * sizeof(int));
//     new[0] = element;
//     free(vector->data);
//     vector->data = new;
//     vector->length++;
// }

void _remove(vector *vec, int pos)
{
    void *new = malloc(vec->size * vec->dataSize);
    void *data = (*vec).data;
    memcpy(new, data, (pos - 1) * vec->dataSize);
    memcpy(new + pos - 1, data + pos, (vec->size - pos + 1) * vec->dataSize);
    free(data);
    vec->data = new;
    vec->length -= 1;
}

void destroy(vector *vec)
{
    free(vec->data);
    vec->length = NULL;
    vec->size = NULL;
}

void reset(vector *vec)
{
    free(vec->data);
    *vec = vec_new(vec->dataSize);
}

#endif