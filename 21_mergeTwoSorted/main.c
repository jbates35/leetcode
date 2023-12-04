#include "uthash.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_TEST 1

///////////// START

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {

  if (list2 == NULL)
    return list1;
  else if (list1 == NULL)
    return list2;

  struct ListNode *head, *p;

  // First entry is a bit different
  if (list1->val < list2->val) {
    head = list1;
    list1 = list1->next;
  } else {
    head = list2;
    list2 = list2->next;
  }

  // Assign p to head so head remains at same place for rtrn
  p = head;

  // Rearrange links while iterating the lists forward
  while (list1 && list2) {
    if (list1->val < list2->val) {
      p->next = list1;
      list1 = list1->next;
    } else {
      p->next = list2;
      list2 = list2->next;
    }
    p = p->next;
  }

  // Attach to the end the remaining list
  p->next = list1 ? list1 : list2;
  return head;
}

//////////// END

void funcTime(struct ListNode *(*fp)(struct ListNode *, struct ListNode *),
              struct ListNode *L1, struct ListNode *L2, char *funcName);
struct ListNode *makeNode(int val);
void createLL(struct ListNode **head, int *arr, int len);
void printLL(struct ListNode *head);
bool checkIfEqualLL(struct ListNode *L1, struct ListNode *L2);
void printArr(int *arr, int len);

int main() {
  int arr1[5][5] = {{1, 2, 4}, {}, {}, {1, 3, 5, 9}, {2}};
  int arr2[5][5] = {{1, 3, 4}, {}, {0}, {2, 4, 6, 8}, {1, 3, 5, 7, 9}};
  int expected[5][10] = {{1, 1, 2, 3, 4, 4},
                         {},
                         {0},
                         {1, 2, 3, 4, 5, 6, 8, 9},
                         {1, 2, 3, 5, 7, 9}};
  int arrLens1[5] = {3, 0, 1, 4, 1};
  int arrLens2[5] = {3, 0, 1, 4, 5};
  int expectedLens[5] = {6, 0, 1, 9, 10};

  for (int i = 0; i < 5; i++) {
    struct ListNode *l1 = NULL, *l2 = NULL, *expectedLL = NULL;

    createLL(&l1, arr1[i], arrLens1[i]);
    createLL(&l2, arr2[i], arrLens2[i]);
    // createLL(&expectedLL, expected[i], expectedLens[i]);
    struct ListNode *result = mergeTwoLists(l1, l2);

    printf("Results for lists %d:\n", i);
    printf("Result: ");
    printLL(l1);
    printLL(l2);
    printLL(result);
    // printf("Expected: ");
    // printLL(expectedLL);
    // printf("Result == Expected: %s\n",
    //        checkIfEqualLL(result, expectedLL) ? "true" : "false");
    printf("\n");
  }
}

struct ListNode *makeNode(int val) {
  struct ListNode *retVal = malloc(sizeof(struct ListNode));
  retVal->val = val;
  retVal->next = NULL;
  return retVal;
}

void createLL(struct ListNode **head, int *arr, int len) {
  if (len == 0 || arr == NULL)
    return;

  struct ListNode *firstNode = makeNode(arr[0]);
  (*head) = firstNode;

  struct ListNode *p = (*head);

  for (int i = 1; i < len; i++) {
    struct ListNode *newNode = makeNode(arr[i]);
    p->next = newNode;
    p = p->next;
  }
}

void printLL(struct ListNode *head) {
  struct ListNode *curr = head;
  while (curr != NULL) {
    printf("%d->", curr->val);
    curr = curr->next;
  }
  printf("NULL\n");
}

bool checkIfEqualLL(struct ListNode *L1, struct ListNode *L2) {
  struct ListNode *curr1 = L1;
  struct ListNode *curr2 = L2;

  while (curr1 != NULL && curr2 != NULL) {
    if (curr1->val != curr2->val)
      return false;
    curr1 = curr1->next;
    curr2 = curr2->next;
  }

  if (curr1 != NULL || curr2 != NULL)
    return false;

  return true;
}

void funcTime(struct ListNode *(*fp)(struct ListNode *, struct ListNode *),
              struct ListNode *L1, struct ListNode *L2, char *funcName) {
  clock_t start = clock();
  for (int i = 0; i < 10000; i++)
    fp(L1, L2);
  clock_t end = clock();

  fflush(stdout);
  printf("Time to run function %s: %f us\n", funcName,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  fflush(stdout);
}
