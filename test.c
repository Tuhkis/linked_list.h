#define LL_IMPL
#include "linked_list.h"
#include "time.h"
#include "stdio.h"

int* ll_int_new(int val) {
  int* a = (int*)(ll_malloc(sizeof(int)));
  *a = val;
  return a;
}

int main() {
  srand(time(NULL));

  int* a  = ll_int_new(2);
  int* a1 = ll_int_new(6);
  int* a2 = ll_int_new(4);
  
  ll_List b = ll_list_new;
  ll_list_add(&b, a);
  ll_list_add(&b, a1);
  ll_list_add(&b, a2);
  for (int i = 0; i < 5; ++i) ll_list_add(&b, ll_int_new(rand() % 20));

  ll_list_remove_ptr(&b, a2);
  ll_list_remove_nth(&b, 0);
  ll_list_remove_nth(&b, 3);

  printf("len = %d\n", b.len);
  ll_list_foreach (b, i) {
    printf("%d\n", ll_iterator_get_data(int, i));
  }
  return 0;
}

