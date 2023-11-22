/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ArrEntry {
  int val;
  int loc;
} ArrEntry;

void mergeSort(int *nums, int lo, int hi);
void mergeWileSorting(int *nums, int lo, int mid, int hi);

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {

  *returnSize = 2;
  int *A = malloc(sizeof(int) * 2);
  int *tempArr = malloc(sizeof(int) * numsSize);

  memcpy(tempArr, nums, sizeof(int) * numsSize);

  mergeSort(tempArr, 0, numsSize - 1);

  int lo = 0;
  int hi = numsSize - 1;

  while (tempArr[lo] + tempArr[hi] != target) {
    if (tempArr[lo] + tempArr[hi] < target)
      lo++;
    else
      hi--;
  }

  int newLo = -1, newHi = -1;
  for (int i = 0; i < numsSize; i++) {
    if (newLo == -1 && tempArr[lo] == nums[i])
      newLo = i;
    else if (newHi == -1 && tempArr[hi] == nums[i])
      newHi = i;

    if (newLo != -1 && newHi != -1)
      break;
  }

  A[0] = newLo;
  A[1] = newHi;
  free(tempArr);
  return A;
}

void mergeSort(int *nums, int lo, int hi) {
  if (hi - lo < 1)
    return;

  int mid = (hi - lo) / 2 + lo;

  mergeSort(nums, lo, mid);
  mergeSort(nums, mid + 1, hi);

  mergeWileSorting(nums, lo, mid, hi);
}

void mergeWileSorting(int *nums, int lo, int mid, int hi) {
  int i = lo;
  int j = mid + 1;
  int k = 0;

  int *tempArr = malloc(sizeof(int) * (hi - lo + 1));
  while (i <= mid && j <= hi) {
    if (nums[i] < nums[j])
      tempArr[k++] = nums[i++];
    else
      tempArr[k++] = nums[j++];
  }

  while (i <= mid)
    tempArr[k++] = nums[i++];
  while (j <= hi)
    tempArr[k++] = nums[j++];

  for (i = 0, j = lo; i < k; i++, j++)
    nums[j] = tempArr[i];

  free(tempArr);
}

int main() {
  // int myNums[] = {2, 0, -4, 13, 12, 9, -3};
  int myNums[] = {3, 3};
  int returnSize;
  int N = sizeof(myNums) / sizeof(int);
  int *A = twoSum(myNums, N, 6, &returnSize);

  printf("The two numbers at position %d and %d\n", A[0], A[1]);
  free(A);
}
