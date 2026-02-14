#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

bool isPalindrome_with_str(int x) {
  char s[12];
  sprintf(s, "%d", x);
  const int l = (int)strlen(s);
  for(int i = 0; i < l; i++) {
    if(s[i] != s[l - i - 1])
      return false;
  }
  return true;
}

#define digit_at(x,p) (x/(int)pow(10,p) % 10)
bool isPalindrome(int x) {
  if(x < 0) return false;
  const int digits = (int)log10((double)x) + 1;
  for(int i = 0; i < digits; i++) {
    if(digit_at(x, i) != digit_at(x, digits - i - 1))
      return false;
  }
  return true;
}

#define BOOL_STR(B) ((B) ? "true" : "false")

void test_pn(int x, bool expected) {
  static int case_count = 0;
  int ret = isPalindrome(x);
  printf("Case%d: %d => %s (%s)\n", case_count++, x, BOOL_STR(ret), BOOL_STR(expected));
  if(ret != expected) {
    fprintf(stderr, "Error: %s:%d: expected %s, found %s\n",
      __FILE_NAME__, __LINE__,
      BOOL_STR(expected), BOOL_STR(ret)
    );
    exit(1);
  }
}

int main(void) {
  puts("");

  test_pn(121, true);
  test_pn(-121, false);
  test_pn(10, false);

  return 0;
}
