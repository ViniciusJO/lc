function isPalinfrome(x: number): boolean {
  const s = String(x);
  for(let i = 0; i <= s.length/2; i++) {
    if(s[i] != s[s.length - i - 1])
      return false;
  }
  return true;
}

let case_count = 0;

function test_pn(x: number, expected: boolean): void {
  const ret = isPalinfrome(x);
  console.log(`Case${case_count++}: ${x} => ${ret} (${expected})`);
  if(ret != expected) throw new Error(`WrongAnswer`);
}

console.log();


test_pn(121, true);
test_pn(-121, false);
test_pn(10, false);
