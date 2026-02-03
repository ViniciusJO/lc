/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function two_sum(arr: number[], target: number): [number, number] {
  const record: Record<number, number> = {};
  for(const i in arr) {
    const missing = target - arr[i];
    if(record[missing] != undefined)
      return [ record[missing], Number(i) ];
    record[arr[i]] = Number(i);
  }
  throw new Error("Two sum not found");
};

console.log("");

{
    const arr = [ 2, 7, 11, 15 ];
    const target = 9;
    const expected = [ 0, 1 ];
    const result = two_sum(arr, target);
    console.log(`Array: ${arr}\nTarget: ${target}\nResult: ${result}\n`);
    if(result[0] != expected[0] || result[1] != expected[1]) throw new Error(`Two sum not found`);
}

{
    const arr = [ 3, 2, 4 ];
    const target = 6;
    const expected = [ 1, 2 ];
    const result = two_sum(arr, target);
    console.log(`Array: ${arr}\nTarget: ${target}\nResult: ${result}\n`);
    if(result[0] != expected[0] || result[1] != expected[1]) throw new Error(`Two sum not found`);
}

{
    const arr = [ 3, 3 ];
    const target = 6;
    const expected = [ 0, 1 ];
    const result = two_sum(arr, target);
    console.log(`Array: ${arr}\nTarget: ${target}\nResult: ${result}\n`);
    if(result[0] != expected[0] || result[1] != expected[1]) throw new Error(`Two sum not found`);
}
