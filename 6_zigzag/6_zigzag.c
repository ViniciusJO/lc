#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY(...) { __VA_ARGS__ }
#define ARRAY_LEN(ARR) (sizeof(ARR)/sizeof(*ARR))


// num_rows = 4
// 0,6,12  [18]
// 1,5,7,11,13 [ 17]
// 2,4,8,10,   [14][16]
// 3,9,  [15]
//

// num_rows = 5
// 0,8,    [16]  +8
// 1,7,9,  [15]  +6,+2
// 2,6,10, [14]  +4
// 3,5,11,13     +2,+6
// 4,12,         +8
//

// num_rows = 10
// 0,18,36,       [54]         +18,+0
// 1,17,19,35,37, [53][55]     +16,+2
// 2,16,20,34,38, [52][56]     +14,+4
// 3,15,21,33,39, [51][57]     +12,+6
// 4,14,22,32,40, [50][58]     +10,+8
// 5,13,23,31,41, [49][59]     +8,+10   -----
// 6,12,24,30,42, [48][60]     +6,+12
// 7,11,25,29,43, [47][61]     +4,+14
// 8,10,26,28,44, [46][62]     +2,+16
// 9,27,45,       [63]         +0,+18




char* convert(char* s, int numRows) {
  int base = numRows - 1;
  if(base == 0) return s;

  int s_len = (int)strlen(s);
  char *ret = (char*)calloc(s_len+1, sizeof(char));
  int count = 0;

  for(int i = 0; i < numRows; i++) {
    int side = 0;
    int incs[2] = { (base-i)*2, i*2 };
    int idx = i;
    // printf("%d [ %d, %d ] => ", i, incs[0], incs[1]);
    while(idx < s_len) {
      // printf("%d, ", idx);
      ret[count++] = s[idx];
      if(!incs[0]) side = 0;
      else if(!incs[1]) side = 1;
      else side = !side;
      idx += side ? incs[0] : incs[1];
    }
    // printf("\n");
  }
  return ret;
}

void test_zzc(char* s, int nrows, char* expected) {
  static int case_count = 0;
  char *ret = convert(s, nrows);
  printf("Case%d: \"%s\" => \"%s\" (\"%s\")\n", case_count++, s, ret, expected);
  if(strcmp(ret, expected)) {
    fprintf(stderr, "Error: %s:%d: expected \"%s\", found \"%s\"\n", __FILE_NAME__, __LINE__, expected, ret);
    exit(1);
  }
}

int main(void) {
  puts("");

  //PAHNAPLSIIGYIR
  //PAHNAPLSIIGYIR
  test_zzc("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
  test_zzc("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
  test_zzc("A", 1, "A");

  return 0;
}
