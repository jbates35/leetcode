#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void funcTime(bool (*fp)(int), int x, char *funcName);

///////////// START
typedef struct node {
  struct node *next;
  struct node *prev;
  int val;
} node;

node *makenode(int val, node *prev) {
  node *thisnode = malloc(sizeof(node));
  thisnode->val = val;
  thisnode->next = NULL;
  thisnode->prev = prev;
  return thisnode;
}

bool isPalindrome(int x) {
  if (x < 0)
    return false;
  if (x < 10)
    return true;

  int reverse = 0;
  long k = 1;
  for (; k * 10 <= x; k *= 10)
    ;

  for (long r = 1; r < k; r *= 10, k /= 10)
    if ((x / k) % 10 != (x / r) % 10)
      return false;
  return true;
}

int main() {
  int nums[] = {-121, 121, 10, 1954664591, 195424591, 1954234591};
  for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
    funcTime(isPalindrome, nums[i], "isPalindrome");
    printf("\n\n");
  }
}

void funcTime(bool (*fp)(int), int x, char *funcName) {
  fflush(stdout);
  clock_t start = clock();
  clock_t end = clock();
  start = clock();
  bool result;
  for (int i = 0; i < 10000; i++)
    result = fp(x);
  end = clock();
  printf("Time to run function %s with val %d is: %f us\n", funcName, x,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Result %d is %s", x, result ? "true" : "false");
  fflush(stdout);
}

// max score is around 1600-1800us for first iteration
