/* A single header library that provides a *NON-TYPE-SAFE* one-directional linked list implementation. */
#ifndef __LL_H__
#define __LL_H__

#ifdef __cplusplus
#ifndef NULL
#define NULL nullptr
#endif /* NULL */
extern "C" {
#endif /* __cplusplus */

/* Ensure NULL is defined. */
#ifndef NULL
#define NULL (0)
#endif /* NULL */

#ifndef LL_NO_STDLIB
#include "stdlib.h"
#endif /* LL_NO_STDLIB */

#ifndef ll_malloc
#define ll_malloc(s) malloc(s)
#endif /* ll_malloc */
#ifndef ll_free
#define ll_free(s) free(s)
#endif /* ll_free */

#define ll_list_new {0, NULL}
#define ll_list_get(l, i) (_ll_list_get_nth_block(&l, (i))->data)
#define ll_list_foreach(list, iterator) for (_ll_Block* iterator = list.first; iterator != NULL; i = (_ll_Block*)(iterator->next))
#define ll_iterator_get_data(type, iterator) *(type *)(iterator->data)

typedef struct {
  void* data; void* next;
} _ll_Block;

typedef struct { unsigned int len; _ll_Block* first; } ll_List;

void ll_list_add(ll_List* list, void* data);
_ll_Block* _ll_list_get_nth_block(ll_List* l, unsigned int n);
void ll_list_remove_ptr(ll_List* list, void* data);
void ll_list_remove_nth(ll_List* list, unsigned int n);

static inline _ll_Block* _ll_block_new() {
  return (_ll_Block*)(ll_malloc(sizeof(_ll_Block)));
}


static inline void ll_list_free(ll_List* l) {
  if (l->len == 0) return;
  for (;l->len > 0; --l->len) {
    _ll_Block* b = l->first;
    for (unsigned int it = 0; it < l->len - 1; ++it) b = (_ll_Block*)(b->next);
    ll_free(b->data);
    ll_free(b);
  }
}

#ifdef LL_IMPL
void ll_list_add(ll_List* list, void* data) {
  if (list->len == 0) {
    list->first = _ll_block_new();
    list->first->data = data;
    ++list->len;
  } else {
    _ll_Block* b = list->first;
    for (unsigned int i = 0; i < list->len - 1; ++i)
      b = (_ll_Block*)(b->next);
    b->next = _ll_block_new();
    b = (_ll_Block*)(b->next);
    b->data = data;
    ++list->len;
  }
}

_ll_Block* _ll_list_get_nth_block(ll_List* l, unsigned int n) {
  if (l->len == 0) return NULL;
  _ll_Block* b = l->first;
  for (unsigned int it = 0; it < n; ++it)
    b = (_ll_Block*)(b->next);
  return b;
}

void ll_list_remove_ptr(ll_List* list, void* data) {
  if (list->len == 1) {
    if (list->first->data == data) { ll_free(list->first->data); ll_free(list->first); }
    list->first = NULL;
    list->len = 0;
    return;
  } else {
    _ll_Block* b = list->first;
    for (unsigned int i = 0; i < list->len - 1; ++i) {
      if (((_ll_Block*)(b->next))->data == data) {
        _ll_Block* nb = (_ll_Block*)(((_ll_Block*)(b->next))->next);
        ll_free(((_ll_Block*)(b->next))->data);
        ll_free(b->next);
        b->next = nb;
        --list->len;
        return;
      }
      b = (_ll_Block*)(b->next);
    }
  }
}

void ll_list_remove_nth(ll_List* list, unsigned int n) {
  if (list->len == 0) return;
  _ll_Block* b = list->first;
  if (n != 0) {
    for (unsigned int it = 0; it < n - 1; ++it)
      b = (_ll_Block*)(b->next);
    _ll_Block* nb = (_ll_Block*)(((_ll_Block*)(b->next))->next);
    ll_free(((_ll_Block*)(b->next))->data);
    ll_free(b->next);
    b->next = nb;
    --list->len;
    return;
  } else {
    _ll_Block* nb = (_ll_Block*)(b->next);
    ll_free(b->data);
    ll_free(b);
    list->first = nb;
    --list->len;
    return;
  }
}

#endif /* LL_IMPL */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LL_H__ */
