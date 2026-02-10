// Naive
function longestPalindrome(s: string): string {
  let palindromes: string[] = [];
  const arr = [...s];

  for(let _c in arr) {
    let i = Number(_c);
    let j = i + 1;
    if(j >= arr.length) break;

    for(;j < arr.length; j++) {
      if(arr[i] == arr[j]) {
        let is_palindrome = true;
        for(let k = 0; k < (j-i)/2; k++) {
          if(arr[i+k] != arr[j-k]) {
            is_palindrome = false;
            break;
          }
        }
        if(is_palindrome) palindromes.push(s.substring(i, j+1));
      }
    }
  }

  return palindromes.sort((a, b) => -(a.length - b.length))[0] ?? arr[0];
};

let case_count = 0;

function test_lps(s: string, expected: string): void {
  const ret = longestPalindrome(s);
  console.log(`Case${case_count++}: "${s}" => "${ret}" ("${expected}")\n`);
  if(ret != expected) throw new Error(`WrongAnswer`);
}

test_lps("babad", "bab");
test_lps("cbbd", "bb");
test_lps("a", "a");
test_lps("ac", "a");


