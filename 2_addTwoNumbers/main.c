/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *makeNode(int val);

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {

  struct ListNode *rootNode = l1;
  int carry = 0;
  struct ListNode *q = NULL;

  while (l1 && l2) {
    int newVal = carry + l1->val + l2->val;
    carry = newVal / 10;
    l1->val = newVal % 10;
    q = l1;
    l1 = l1->next;
    l2 = l2->next;
  }

  struct ListNode *remainHunk = NULL;
  if (l2) {
    q->next = l2;
    l1 = q->next;
  }

  while (carry && l1) {
    int newVal = carry + l1->val;
    carry = newVal / 10;
    l1->val = newVal % 10;
    q = l1;
    l1 = l1->next;
  }
  if (carry) {
    q->next = makeNode(carry);
  }

  return rootNode;
}

struct ListNode *makeNode(int val) {
  struct ListNode *newNode = malloc(sizeof(struct ListNode));
  newNode->val = val;
  newNode->next = NULL;
  return newNode;
}

int main() {
  int A[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  int B[] = {5, 6, 4};
  //
  // int A[] = {9, 9, 9, 9, 9, 9, 9};
  // int B[] = {9, 9, 9, 9};

  struct ListNode *A_LL, *B_LL, *AT;

  A_LL = makeNode(A[0]);
  B_LL = makeNode(B[0]);
  AT = makeNode(A[0]);

  struct ListNode *tA_LL = A_LL;
  struct ListNode *tB_LL = B_LL;
  struct ListNode *tAT_LL = AT;
  for (int i = 1; i < sizeof(A) / sizeof(int); i++) {
    tA_LL->next = makeNode(A[i]);
    tAT_LL->next = makeNode(A[i]);
    tA_LL = tA_LL->next;
    tAT_LL = tAT_LL->next;
  }
  for (int i = 1; i < sizeof(B) / sizeof(int); i++) {
    tB_LL->next = makeNode(B[i]);
    tB_LL = tB_LL->next;
  }

  struct ListNode *C = addTwoNumbers(A_LL, B_LL);

  while (AT) {
    printf("%d, ", AT->val);
    AT = AT->next;
  }
  printf("\n\n");
  while (B_LL) {
    printf("%d, ", B_LL->val);
    B_LL = B_LL->next;
  }
  printf("\n\n");
  while (C) {
    printf("%d, ", C->val);
    C = C->next;
  }
}
/*
*
  int carry = 0;

  struct ListNode *l3_root = makeNode(l1->val + l2->val);
  struct ListNode *l3 = l3_root;
  l1 = l1->next;
  l2 = l2->next;

  while (l1 && l2) {
    struct ListNode *tempNode = makeNode((l1->val + l2->val + carry) % 10);
    carry = (l1->val + l2->val + carry) / 10;

    l3->next = tempNode;
    l3 = l3->next;
    l1 = l1->next;
    l2 = l2->next;
  }

  while (l1) {
    l3->next = makeNode((l1->val + carry) % 10);
    carry = (l1->val + carry) / 10;
    l3 = l3->next;
  }

  while (l2) {
    l3->next = makeNode((l2->val + carry) % 10);
    carry = (l2->val + carry) / 10;
    l3 = l3->next;
  }

  if (carry)
    l3->next = makeNode(carry);

  return l3_root;
*/
