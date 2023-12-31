#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
// this is incredibly shit
#define define_list(type)                                                      \
  struct _vector;                                                              \
                                                                               \
  typedef struct _vector_##type {                                              \
    type *data;                                                                \
    size_t size;                                                               \
    size_t length;                                                             \
    /* do not do this - function pointers in a struct are retarded*/           \
    void (*prepend)(struct _vector_##type * vector, type element);             \
    void (*append)(struct _vector_##type * vector, type element);              \
    void (*remove)(struct _vector_##type * vector, int position);              \
    void (*destroy)(struct _vector_##type * vector);                           \
    void (*reset)(struct _vector_##type * vector);                             \
    void (*shrink)(struct _vector_##type * vector);                            \
  } _vector_##type;                                                            \
  /*adds an array entry to the end of the vector*/                             \
  void _append_##type(struct _vector_##type *vector, type element) {           \
    type *new;                                                                 \
    if (vector->length + 1 > vector->size) {                                   \
      new = (type *)malloc(vector->size * 2 * sizeof(type));                   \
      memcpy(new, vector->data, vector->size * sizeof(type));                  \
      free(vector->data);                                                      \
      vector->data = new;                                                      \
      vector->size *= 2;                                                       \
    }                                                                          \
    vector->data[vector->length] = element;                                    \
    vector->length++;                                                          \
  }                                                                            \
  /*adds an array entry to the beginning of the vector*/                       \
  void _prepend_##type(struct _vector_##type *vector, type element) {          \
    vector->size =                                                             \
        vector->length + 1 > vector->size ? vector->size *= 2 : vector->size;  \
    type *new = (type *)malloc(vector->size * sizeof(type));                   \
    memcpy(new + 1, vector->data, vector->length * sizeof(type));              \
    new[0] = element;                                                          \
    free(vector->data);                                                        \
    vector->data = new;                                                        \
    vector->length++;                                                          \
  }                                                                            \
  /*removes the entry of a vector at pos*/                                     \
  void _remove_##type(struct _vector_##type *vector, int pos) {                \
    type *new = malloc(vector->size * sizeof(type));                           \
    type *data = (*vector).data;                                               \
    memcpy(new, data, (pos - 1) * sizeof(type));                               \
    memcpy(new + pos - 1, data + pos,                                          \
           (vector->size - pos + 1) * sizeof(type));                           \
    free(data);                                                                \
    vector->data = new;                                                        \
    vector->length -= 1;                                                       \
  }                                                                            \
  /*destroys the data of the vector*/                                          \
  void _destroy_##type(struct _vector_##type *vector) {                        \
    free(vector->data);                                                        \
    vector->length = NULL;                                                     \
    vector->size = NULL;                                                       \
  }                                                                            \
  /*resets the vector to the default settings*/                                \
  void _reset_##type(struct _vector_##type *vector) {                          \
    free(vector->data);                                                        \
    (*vector).data = (type *)malloc(10 * sizeof(type));                        \
    (*vector).size = 10;                                                       \
    (*vector).length = 0;                                                      \
  }                                                                            \
  /*shrinks the vector size to the length*/                                    \
  void _shrink_to_length_##type(struct _vector_##type *vector) {               \
    type *new = malloc(vector->length * sizeof(type));                         \
    memcpy(new, vector->data, vector->length * sizeof(type));                  \
    free((*vector).data);                                                      \
    vector->data = new;                                                        \
    vector->size = vector->length;                                             \
  }                                                                            \
  /*vector initialization*/                                                    \
  _vector_##type _new_vector_##type() {                                        \
    _vector_##type ret;                                                        \
    ret.data = (type *)malloc(10 * sizeof(type));                              \
    ret.size = 10;                                                             \
    ret.length = 0;                                                            \
    ret.append = &_append_##type;                                              \
    ret.prepend = &_prepend_##type;                                            \
    ret.remove = &_remove_##type;                                              \
    ret.reset = &_reset_##type;                                                \
    ret.destroy = &_destroy_##type;                                            \
    ret.shrink = &_shrink_to_length_##type;                                    \
    return ret;                                                                \
  }

#define vector(type) _vector_##type
#define new_vector(type) _new_vector_##type()

#endif