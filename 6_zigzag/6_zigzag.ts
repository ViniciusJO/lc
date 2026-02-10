// Naive
function convert(s: string, numRows: number): string {
  if(numRows == 1) return s;
  const arr: string[][] = new Array(numRows);

  let direction: `down` | `up` = `down`;
  let row = 0;
  for(const c of [...s]) {
    if(!arr[row]) arr[row] = [c];
    else arr[row].push(c);

    if(direction == `down` && row == numRows - 1) direction = `up`;
    else if(direction == `up` && row == 0) direction = `down`;

    if(direction == `down`) row++;
    else row--;
  }

  return arr.flatMap(el => el).reduce((a, b) => a + b, "");
}

let case_count = 0;

function test_zzc(s: string, numRows:number, expected: string): void {
  const ret = convert(s, numRows);
  console.log(`Case${case_count++}: "${s}" => "${ret}" ("${expected}")`);
  if(ret != expected) throw new Error(`WrongAnswer`);
}

console.log();

test_zzc("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
test_zzc("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
test_zzc("A", 1, "A");

