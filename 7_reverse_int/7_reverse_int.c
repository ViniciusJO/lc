#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY(...) { __VA_ARGS__ }
#define ARRAY_LEN(ARR) (sizeof(ARR)/sizeof(*ARR))

int reverse(int x) {
  int ret = 0;
  int rem = 0;
  for(int i = 1; i < 10; i++) {
    rem = x % 10;
    x = x / 10; 
    ret = ret * 10 + rem;
    if(x == 0) break;
    printf("x = %d, rem = %d, ret = %d\n", x, rem, ret);
  }
  if(x) {
    if(
      ret < INT32_MIN/10 ||
      ret > INT32_MAX/10 ||
      (ret == INT32_MIN/10 && x < INT32_MIN%10) ||
      (ret == INT32_MAX/10 && x > INT32_MAX%10)
    ) return 0;
    ret = ret * 10 + x;
  }
  return ret;
}

void test_ri(int x, int expected) {
  static int case_count = 0;
  int ret = reverse(x);
  printf("Case%d: %d => %d (%d)\n", case_count++, x, ret, expected);
  if(ret != expected) {
    fprintf(stderr, "Error: %s:%d: expected %d, found %d\n", __FILE_NAME__, __LINE__, expected, ret);
    exit(1);
  }
}

int main(void) {
  puts("");

  test_ri(123, 321);
  test_ri(-123, -321);
  test_ri(120, 21);
  test_ri(1534236469, 0);
  test_ri(-1463847412, -2147483641);

      return 0;
}
