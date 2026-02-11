#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ARRAY(...) { __VA_ARGS__ }
#define ARRAY_LEN(ARR) (sizeof(ARR)/sizeof(*ARR))

int myAtoi(char* s) {
  while(*s == ' ') s++;
  int negative = *s == '-' ? (s++, 1) : *s == '+' ? (s++, 0) : 0;
  int ret = 0;
  int nlz = 0;
  for(int i = 0; i < (int)strlen(s) && (s[i] >= '0' && s[i] <= '9'); i++) {
    char c = s[i] - '0';
    if(ret == 0 && s[i] == '0') continue;
    // printf("\t%d: %d * 10 + %d\n", i, ret, c);
    if(nlz == 9) {
      if(ret > INT32_MAX / 10) return negative ? INT32_MIN : INT32_MAX;
      else if(!negative && ret == INT32_MAX/10 && (c) > INT32_MAX % 10) {
          return INT32_MAX;
      } else if(ret == INT32_MIN/-10 && (c) >= -(INT32_MIN % 10)) {
          return INT32_MIN;
      }
    } else if(nlz > 9) return negative ? INT32_MIN : INT32_MAX; 
    ret = ret * 10 + c;
    nlz++;
  }
  return negative ? -ret : ret;
}

void test_atoi(char* s, int expected) {
  static int case_count = 0;
  int ret = myAtoi(s);
  printf("Case%d: \"%s\" => %d (%d)\n", case_count++, s, ret, expected);
  if(ret != expected) {
    fprintf(stderr, "Error: %s:%d: expected %d, found %d\n", __FILE_NAME__, __LINE__, expected, ret);
    exit(1);
  }
}

#define TO_STR_(X) #X
#define TO_STR(X) TO_STR_(X)

int main(void) {
  puts("");

  test_atoi("42", 42);
  test_atoi("   -042", -42);
  test_atoi("1337c0d3", 1337);
  test_atoi("0-1", 0);
  test_atoi("words and 987", 0);
  test_atoi("-91283472332", INT32_MIN);
  test_atoi("  0000000000012345678", 12345678);
  test_atoi("-2147483648", -2147483648);
  test_atoi("21474836478", INT32_MAX);
  test_atoi("-21474836488", INT32_MIN);

  return 0;
}
