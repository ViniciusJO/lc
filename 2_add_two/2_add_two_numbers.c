#include <stdio.h>
#include <stdlib.h>

#define HEAP_ALLOC(TYPE,N) (TYPE*)malloc(N*sizeof(TYPE))

#define ARRAY_LEN(ARR) (sizeof(ARR)/sizeof(*ARR))
#define ARRAY(...) { __VA_ARGS__ }

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *ll_from_arr_(int *array, int length) {
  if(length == 0) return NULL;
  struct ListNode *ret = HEAP_ALLOC(struct ListNode, 1);
  *ret = (struct ListNode){ .val = *array, .next = ll_from_arr_(array+1, length-1) };
  return ret;
}
#define ll_from_arr(ARRAY) ll_from_arr_(ARRAY, ARRAY_LEN(ARRAY))

void ll_free(struct ListNode *ll) {
  if(ll->next != NULL) ll_free(ll->next);
  free(ll);
}

void ll_print(struct ListNode *ll) {
  if(ll == NULL) return;
  printf("%d%s", ll->val, ll->next != NULL ? " -> " : "");
  ll_print(ll->next);
}

void print_operation(struct ListNode* l1, struct ListNode* l2, struct ListNode* result) {
  printf("(");
  ll_print(l1);
  printf(") + (");
  ll_print(l2);
  printf(") = (");
  ll_print(result);
  printf(")\n");
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  static struct ListNode sum_empty = { .val = 0, .next = NULL };

  struct ListNode *it1 = l1;
  struct ListNode *it2 = l2;
  int carry = 0;
  struct ListNode* ret = HEAP_ALLOC(struct ListNode, 1);
  struct ListNode* constructor = ret;

  for(;; constructor = constructor->next) {
    int sum = it1->val + it2->val + carry;
    int val = sum % 10;
    // printf("%d + %d + %d = %d (v = %d, c = %d)\n", it1->val, it2->val, carry, sum, val, sum/10);
    carry = sum/10;
    constructor->val = val;
    if(it1->next == NULL && it2->next == NULL) break;
    it1 = (it1->next != NULL) ? it1->next : &sum_empty;
    it2 = (it2->next != NULL) ? it2->next : &sum_empty;
    constructor->next = HEAP_ALLOC(struct ListNode, 1);
    constructor->next->next = NULL;
  }

  if(carry) {
    constructor->next = HEAP_ALLOC(struct ListNode, 1);
    constructor->next->val = carry;
    constructor->next->next = NULL;
  }

  print_operation(l1, l2, ret);

  return ret;
}


int ll_compare(struct ListNode *l1, struct ListNode *l2) {
  struct ListNode *it1 = l1;
  struct ListNode *it2 = l2;
  while(it1 != NULL && it2 != NULL) {
    // printf("%d == %d ? %s\n", it1->val, it2->val, it1->val == it2->val ? "true" : "false");
    if(it1->val != it2->val) return 0;
    it1 = it1->next;
    it2 = it2->next;
  }

  return (it1 != NULL || it2 != NULL) ? 0 : 1;
}

#define ATN_TEST(ARR1, ARR2, EXPECTED) do { \
  int array1[] = ARR1; \
  int array2[] = ARR2; \
  int expected[] = EXPECTED; \
 \
  struct ListNode *list1 = ll_from_arr(array1); \
  struct ListNode *list2 = ll_from_arr(array2); \
  struct ListNode *list_expected = ll_from_arr(expected); \
 \
  struct ListNode *result = addTwoNumbers(list1, list2); \
 \
  int compare = ll_compare(list_expected, result); \
 \
  printf("("); \
  ll_print(list_expected); \
  printf(") == ("); \
  ll_print(result); \
  printf(") ? %s\n\n", compare ? "true" : "false"); \
 \
  ll_free(list1); \
  ll_free(list2); \
  ll_free(list_expected); \
  ll_free(result); \
 \
  if(!compare) { \
    fprintf(stderr, "ERROR:%s:%d: resultado diferente do esperado\n", __FILE_NAME__, __LINE__); \
    exit(1); \
  } \
 \
} while(0) \

int main(void) {
  ATN_TEST(ARRAY(2, 4, 3), ARRAY(5, 6, 4), ARRAY(7, 0, 8));
  ATN_TEST(ARRAY(0), ARRAY(0), ARRAY(0));
  ATN_TEST(ARRAY(9, 9, 9, 9, 9, 9, 9), ARRAY(9, 9, 9, 9), ARRAY(8, 9, 9, 9, 0, 0, 0, 1));

  return 0;
}
