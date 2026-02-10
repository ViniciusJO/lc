function reverse(x: number): number {
    const str = [...x.toString()];
    let is_neg = false;
    if(str[0] == "-") {
        is_neg = true;
        str.shift();
    }
    const ret = (is_neg ? -1 : 1) * Number( str.reverse().reduce((a,b) => a + b, "") );
    if(ret <= -1*2**31 || ret >= 2**31 - 1) return 0;
    return ret;
};

let case_count = 0;

function test_ri(x: number, expected: number): void {
  const ret = reverse(x);
  console.log(`Case${case_count++}: ${x} => ${ret} (${expected})`);
  if(ret != expected) throw new Error(`WrongAnswer`);
}

console.log();

test_ri(123, 321);
test_ri(-123, -321);
test_ri(120, 21);
test_ri(1534236469, 0);

