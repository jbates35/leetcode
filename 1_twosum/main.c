
/*
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct ArrADT {
  int *A;
  int size;
  int l;
} ArrADT;

void addBinArr(ArrADT *arr, int val);
void algs_radixSort_altered(int *A, int N);

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {

  *returnSize = 2;
  int *A = malloc(sizeof(int) * 2);
  int *tempArr = malloc(sizeof(int) * numsSize);

  memcpy(tempArr, nums, sizeof(int) * numsSize);

  algs_radixSort_altered(tempArr, numsSize);

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

void algs_radixSort_altered(int *A, int N) {
  if (A == NULL) {
    fflush(stdout);
    fprintf(stderr, "\nError: Null pointer in algs_radixSort\n");
    return;
  }

  int maxVal = A[0];
  int minVal = A[0];
  for (int i = 1; i < N; i++) {
    if (maxVal < A[i])
      maxVal = A[i];
    if (minVal > A[i])
      minVal = A[i];
  }

  int absMaxVal = maxVal;
  int absMinVal = abs(minVal);
  if (absMaxVal < absMinVal)
    absMaxVal = absMinVal;

  ArrADT *bins[32] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                      NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                      NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                      NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

  for (int i = 0; i < 32; i++) {
    bins[i] = malloc(sizeof(ArrADT));
    bins[i]->size = 100;
    bins[i]->A = malloc(sizeof(int) * bins[i]->size);
    bins[i]->l = 0;
  }

  for (int bitsh = 1; (absMaxVal / bitsh) != 0; bitsh *= 16) {
    // First sort array values into the bins
    for (int i = 0; i < N; i++) {
      int binNo = (A[i] / bitsh) % 16 + 16;
      addBinArr(bins[binNo], A[i]);
    }

    // Now pop the bins in order back into the array
    int aInd = 0;
    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < bins[i]->l; j++)
        A[aInd++] = bins[i]->A[j];
      bins[i]->l = 0;
    }
  }

  for (int i = 0; i < 32; i++) {
    free(bins[i]->A);
    free(bins[i]);
  }
}

void addBinArr(ArrADT *arr, int val) {
  arr->l++;
  if (arr->l >= arr->size) {
    arr->size *= 2;
    arr->A = realloc(arr->A, sizeof(int) * arr->size);
  }
  arr->A[arr->l - 1] = val;
}

int main() {
  int myNums[] = {2, 0, 124, 90, 1024, -105365, -4, 13, 12, 9, -3};
  // int myNums[] = {3, 3};
  int returnSize;
  int N = sizeof(myNums) / sizeof(int);
  int *A = twoSum(myNums, N, -105365, &returnSize);

  printf("The two numbers at position %d and %d\n", A[0], A[1]);
  free(A);
}
