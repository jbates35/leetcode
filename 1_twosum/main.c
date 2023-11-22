/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void quickSort(int *nums, int lo, int hi);
int findMiddle(int *A, int m, int n);
void swap(int *x, int *y);

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {

  *returnSize = 2;
  int *A = malloc(sizeof(int) * 2);
  int *tempArr = malloc(sizeof(int) * numsSize);

  memcpy(tempArr, nums, sizeof(int) * numsSize);

  quickSort(tempArr, 0, numsSize);

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

void quickSort(int *nums, int lo, int hi) {
  if (hi - lo <= 1)
    return;
  swap(&nums[lo], &nums[findMiddle(nums, lo, hi)]);

  int pivot = nums[lo];

  int i = lo + 1;
  int j = hi - 1;

  do {
    if (nums[i] > pivot && nums[j] <= pivot)
      swap(&nums[i], &nums[j]);
    if (nums[i] <= pivot)
      i++;
    if (nums[j] > pivot)
      j--;
  } while (i <= j);

  swap(&nums[lo], &nums[j]);

  quickSort(nums, i, hi);
  quickSort(nums, lo, j);
}

int findMiddle(int *A, int m, int n) {
  int lo = A[m];
  int midInd = (m + n) / 2;
  int mid = A[midInd];
  int hi = A[n - 1];

  if ((lo < mid && mid < hi) || (hi < mid && mid < lo))
    return midInd;
  if ((lo < hi && hi < mid) || (mid < hi && hi < lo))
    return n - 1;
  else
    return m;
}

void swap(int *x, int *y) {
  int temp = *y;
  *y = *x;
  *x = temp;
}

int main() {
  int myNums[] = {2, 0, -4, 13, 12, 9, -3};
  // int myNums[] = {3, 3};
  int returnSize;
  int N = sizeof(myNums) / sizeof(int);
  int *A = twoSum(myNums, N, 11, &returnSize);

  printf("The two numbers at position %d and %d\n", A[0], A[1]);
  free(A);
}
