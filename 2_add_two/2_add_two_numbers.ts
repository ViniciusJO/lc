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

class ListNode {
  val: number
  next: ListNode | null
  constructor(val?: number, next?: ListNode | null) {
    this.val = (val===undefined ? 0 : val)
    this.next = (next===undefined ? null : next)
  }
}


function addTwoNumbers_rec(l1: ListNode | null, l2: ListNode | null, carry: number): ListNode | null {
  const list1 = l1 ?? new ListNode(0, null);
  const list2 = l2 ?? new ListNode(0, null);
  let value = list1.val + list2.val + carry;
  let c = Math.trunc(value / 10);
  if(!list1.next && !list2.next)
    return new ListNode(value % 10, c ? new ListNode(c, null) : null);
  return new ListNode(value % 10, addTwoNumbers_rec(list1.next, list2.next, c));
}

function addTwoNumbers(l1: ListNode | null, l2: ListNode | null): ListNode | null {
  return addTwoNumbers_rec(l1, l2, 0);
};


function ll_from_array_(array: number[]): ListNode | null {
  const [fe, ...tail] = array;
  return new ListNode(fe, tail.length != 0 ? ll_from_array(tail) : null);
}

function ll_from_array(array: number[]): ListNode {
  return ll_from_array_(array) ?? new ListNode();
}

function array_from_ll(ll: ListNode | null): number[] {
  if(!ll) return [];
  return [ll.val, ...array_from_ll(ll.next)];
}


const error = () => { throw new Error(`Failed to add two lists`); };

function atn_test(array1: number[], array2: number[], expect: number[]): void {
  const list1  = ll_from_array(array1);
  const list2  = ll_from_array(array2);
  const expect_list = ll_from_array(expect);

  const result = addTwoNumbers(list1, list2);

  console.log(array1, ` + `, array2, ` = `, array_from_ll(result), `\n`);

  if(result) {
    let it_e: ListNode | null = expect_list;
    let it_r: ListNode | null = result;


    while(it_e && it_r) {
      if(it_e.val != it_r.val) error();
      it_e = it_e.next;
      it_r = it_r.next;
    }

    if(it_e || it_r) error();

  } else error();
}

atn_test([2, 4, 3], [5, 6, 4], [7, 0, 8]);
atn_test([0], [0], [0]);
atn_test([9, 9, 9, 9, 9, 9, 9], [9, 9, 9, 9], [8, 9, 9, 9, 0, 0, 0, 1]);
  
