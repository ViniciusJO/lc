#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(A, B) (((A) > (B)) ? (A) : (B))

int lengthOfLongestSubstring(char* s) {
  int length = (int)strlen(s);
  int char_pos[256];
  memset(char_pos, -1, 256 * sizeof(int));
  int p1 = 0, p2 = 0;
  int count = 0;

  while(p1 < length && p2  < length) {
    int current = (int)s[p2];
    if(char_pos[current] >= 0)
      p1 = MAX(p1, char_pos[current] + 1);
    char_pos[current] = p2;
    p2 += 1;
    count = MAX(count, p2 - p1);
  }

  return count;
}

void test_lss(char *s, int expected) {
  static int case_count = 0;
  int result = lengthOfLongestSubstring(s);
  fprintf(stdout, "\nCase_%d: \"%s\" => %d (%d)\n", case_count++, s, result, expected);
  fflush(stdout);
  if(result != expected) {
    fprintf(stderr, "Error: processing string \"%s\"\n\t\texpected: %d\n\t\treceiver: %d\n\n", s, expected, result);
    fflush(stderr);
    exit(1);
  }
}

int main(void) {
  char asci_alphabet[128];
  for(int i = 0; i < 127; i++) asci_alphabet[i] = i + 1;
  asci_alphabet[127] = 0;

  test_lss(asci_alphabet, 127);
  test_lss("abcdefghijklmnopqrstuvwxyz", 26);
  test_lss("abcabcbb", 3);
  test_lss("bbbbb", 1);
  test_lss("pwwkew", 3);
  test_lss(" ", 1);
  test_lss("abba", 2);

  return 0;
}
