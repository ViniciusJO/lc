#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY(...) { __VA_ARGS__ }
#define ARRAY_LEN(ARR) (sizeof(ARR)/sizeof(*ARR))

char* longestPalindrome(char* s) {
  int lp[2] = { 0, 0 };
  int s_len = (int)strlen(s);
  int j;
  int can_be_even;
  for(int i = 1; i < s_len; i++) {
    j = 1;
    can_be_even = 0;
    while(1) {
      if(i-j-can_be_even < 0 || i+j > s_len) break;
      if(s[i-j-can_be_even] != s[i+j]) {
        if(!can_be_even && s[i-1] == s[i]) {
          j = can_be_even = 1;
          if(2 > lp[1] - lp[0]) { lp[0] = i-1; lp[1] = i; }
        } else break;
      } else {
        if(2*j+can_be_even > lp[1] - lp[0]) {
          lp[0] = i-j-can_be_even;;
          lp[1] = i+j;
        }
        j++;
      }
    }

  }
  return strndup(s+lp[0], lp[1] - lp[0] + 1);
}

void test_lps(char* s, char* expected) {
  static int case_count = 0;
  char *ret = longestPalindrome(s);
  printf("Case%d: \"%s\" => \"%s\" (\"%s\")\n", case_count++, s, ret, expected);
  if(strcmp(ret, expected)) {
    fprintf(stderr, "Error: %s:%d: expected \"%s\", found \"%s\"\n", __FILE_NAME__, __LINE__, expected, ret);
    exit(1);
  }
}

int main(void) {
  puts("");

  test_lps("babad", "bab");
  test_lps("ovo", "ovo");

  test_lps("cbbd", "bb");
  test_lps("a", "a");
  test_lps("ac", "a");
  test_lps("dbbd", "dbbd");
  test_lps("adbbdx", "dbbd");
  test_lps("adbbdaxx", "adbbda");
  test_lps("adbbdaxxadbb", "bbdaxxadbb");

  test_lps("bb", "bb");
  return 0;
}
