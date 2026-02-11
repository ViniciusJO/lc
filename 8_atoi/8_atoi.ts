const INT32_MIN = -2147483648;
const INT32_MAX = 2147483647;

function myAtoi(s: string): number {
  const INT32_MIN = -2147483648;
  const INT32_MAX = 2147483647;
  const is_digit = (c: string): boolean =>
    Boolean(c) && (c.charCodeAt(0) >= "0".charCodeAt(0) && c.charCodeAt(0) <= "9".charCodeAt(0));

  let i = 0;
  while(s[i] == " ") i++;

  let sign = 1;
  if(s[i] == "+") i++;
  else if(s[i] == "-") { sign = -1; i++; }

  let ret = 0;
  while(is_digit(s[i])) {
    ret = ret * 10 + (s[i].charCodeAt(0) - "0".charCodeAt(0));
    if(sign > 0 && ret >= INT32_MAX) return INT32_MAX;
    else if(sign < 0 && sign * ret <= INT32_MIN) return INT32_MIN;
    i++;
  }
  return sign * ret;
};

let case_count = 0;

function test_atoi(s: string, expected: number): void {
  const ret = myAtoi(s);
  console.log(`Case${case_count++}: "${s}" => ${ret} (${expected})`);
  if(ret != expected) throw new Error(`WrongAnswer`);
}

console.log();


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
