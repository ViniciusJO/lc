#include <stdlib.h>
#include <stdio.h>
#include <uthash.h>

typedef struct {
  int id;
  int field;
  UT_hash_handle hh;
} Storage;

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  Storage *storage = NULL;
  for(int i =0; i < numsSize; i++) {
    const int comp = target - nums[i];
    Storage *saida = NULL;
    HASH_FIND_INT(storage, &comp, saida);
    if(saida != NULL) {
      int *ret = (int*)malloc(2*sizeof(int));
      ret = (int[]){ saida->field, i };
      *returnSize = 2;
      return ret;
    } else {
      Storage *s = (Storage*)malloc(sizeof(Storage));
      *s = (Storage){ .id = nums[i], .field = i };
      HASH_ADD_INT(storage, id, s);
    }
  }
  
  *returnSize = 0;
  return NULL;
}

#define ARRAY(...) { __VA_ARGS__ }
#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY)/sizeof(*ARRAY))
#define TEST_TWO_SUM(EXPECTED, TARGET, ARRAY_) do { \
  int arr[] = ARRAY_; \
  int target = TARGET; \
  int expected[2] = EXPECTED; \
  int rs = 0; \
  int *result = twoSum(arr, ARRAY_SIZE(arr), target, &rs); \
  if(result == NULL || rs != 2 || result[0] != expected[0] || result[1] != expected[1]) { \
    fprintf(stderr, "Error: %s:%d: Two sum error\n\texpected: { %d, %d }\n\tfound: { ", \
      __FILE_NAME__, __LINE__, \
      expected[0], expected[1] \
    ); \
    for(int i =0; i < rs; i++) fprintf(stderr, "%d%s", result[i], i == rs-1 ? " " : ", "); \
    fprintf(stderr, "}\n"); \
    exit(1); \
  } else { \
    fprintf(stdout, "Success: int input[] = { " ); \
    for(int i = 0; i < (int)ARRAY_SIZE(arr); i++) \
      fprintf(stdout, "%d%s", arr[i], i == (int)ARRAY_SIZE(arr) - 1 ? " " : ", "); \
    fprintf(stdout, "}\n\tinput[%d] + input[%d] = target\t\t==>\t\t%d + %d = %d\n\n", \
      expected[0], expected[1], arr[expected[0]], arr[expected[1]], target \
    ); \
  } \
} while(0)


int main(void) {

  //            EXPECTED  TARGET  INPUT
  TEST_TWO_SUM(ARRAY(0 ,1), 9, ARRAY(2, 7, 11, 15));
  TEST_TWO_SUM(ARRAY(1, 2), 6, ARRAY(3, 2, 4));
  TEST_TWO_SUM(ARRAY(0 ,1), 6, ARRAY(3, 3));
  
  return 0;
}
