function lengthOfLongestSubstring(s: string): number {
  const lp: Record<string, number> = {};
  const arr = [...s];
  let p1 = 0, p2 = 0;

  let counter = 0;

  while(p1 < arr.length && p2 < arr.length) {
    const char = arr[p2];
    if(lp[char] != undefined) {
      let out = ``;
      for(let i = p1; i < p2; i++) {
        out += arr[i]        ;
      }
      console.log(out);
      p1 = lp[char] + 1;
    }
    lp[char] = p2;
    counter = Math.max(counter, p2 - p1 + 1);
    p2++;
  }

  return counter;
};

let case_count = 0;
function test_lss(s: string, expected: number): void {
  const res = lengthOfLongestSubstring(s);
  console.log(`Case_${case_count++}: "${s}" => ${res} (expected: ${expected})`);
  if(res != expected) throw new Error(`ERROR: Wrong result:\n\texpected: ${expected}\n\treceived: ${res}`);
}

const asci_alphabet = [...Array(256).keys()].map(e => String.fromCharCode(e)).reduce((a,c) => a + c, ``);

//*
// test_lss(asci_alphabet, 256);
// test_lss(`abcdefghijklmnopqrstuvwxyz`, 26);
// test_lss(`abcabcbb`, 3);
// test_lss(`bbbbb`, 1);
// test_lss(`pwwkew`, 3);
// test_lss(` `, 1);
test_lss(`abba`, 2);
/**/
