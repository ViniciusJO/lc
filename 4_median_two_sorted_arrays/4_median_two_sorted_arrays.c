#include <stdio.h>
#include <stdlib.h>

#define ARRAY(...) { __VA_ARGS__ }
#define ARRAY_LEN(ARR) (sizeof(ARR)/sizeof(*ARR))

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  const int new_size = (nums1Size + nums2Size);
  int *new_array = (int*)malloc(new_size * sizeof(int));
  int it1 = 0, it2 = 0;

  for(int i = 0; i < new_size; i++) {
    if(it1 == nums1Size) new_array[i] = nums2[it2++];
    else if(it2 == nums2Size) new_array[i] = nums1[it1++];
    else new_array[i] = (nums1[it1] < nums2[it2]) ? nums1[it1++] : nums2[it2++];
  }

  int low_mid_idx = new_size / 2 - 1;
  double ret;
  if(new_size % 2 != 0) ret =  (double)new_array[low_mid_idx + 1];
  else ret = (double)(new_array[low_mid_idx] + new_array[low_mid_idx + 1]) / 2.0;
  free(new_array);
  return ret;
}

void _test_mts(int* nums1, int nums1Size, int* nums2, int nums2Size, double expected) {
  static int case_count = 0;
  double ret = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);
  printf("Case%d: [ ", case_count++);
  for(int i = 0; i < nums1Size; i++) printf("%d%s", nums1[i], i != nums1Size - 1 ? ", " : " ");
  printf("], [ ");
  for(int i = 0; i < nums2Size; i++) printf("%d%s", nums2[i], i != nums2Size - 1 ? ", " : " ");
  printf("] => %f (%f)\n\n", ret, expected);
  if(ret != expected) {
    fprintf(stderr, "Error: %s:%d: expected %f, found %f\n", __FILE_NAME__, __LINE__, expected, ret);
    exit(1);
  }
}
#define test_mts(NUMS1, NUMS2, EXPECTED) do { \
  int n1[] = NUMS1; \
  int n2[] = NUMS2; \
  _test_mts(n1, ARRAY_LEN(n1), n2, ARRAY_LEN(n2), EXPECTED); \
} while(0)


int main(void) {

  test_mts(ARRAY(1,3), ARRAY(2), 2);
  test_mts(ARRAY(1,2), ARRAY(3,4), 2.5);
  test_mts(ARRAY(1,2,3,4,5), ARRAY(6,7,8,9,10,11,12,13,14,15,16,17), 9);

  return 0;
}
