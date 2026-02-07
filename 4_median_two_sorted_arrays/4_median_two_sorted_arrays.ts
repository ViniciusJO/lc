function findMedianSortedArrays(nums1: number[], nums2: number[]): number {
  const na = [ ...nums1, ...nums2 ].sort((a, b) => a - b);
  if(na.length % 2 != 0) return na[(na.length-1)/2];
  const lm = (na.length - 2) / 2;
  return (na[lm] + na[lm + 1])/2;
};

let case_count = 0;

function test_mts(nums1: number[], nums2: number[], expected: number): void {
  const ret = findMedianSortedArrays(nums1, nums2);
  console.log(`Case${case_count++}: [${nums1}], [${nums2}] => ${ret} (${expected})\n`);
  if(ret != expected) throw new Error(`WrongAnswer`);
}

test_mts([1,3], [2], 2);
test_mts([1,2], [3,4], 2.5);
test_mts([1,2,3,4,5], [6,7,8,9,10,11,12,13,14,15,16,17], 9);


