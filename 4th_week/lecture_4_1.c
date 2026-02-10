/* header files */
#include <stdio.h>
#include <stdlib.h>

/* define */
#define STR_MAX 256

/* structure */
typedef struct node {
  int key;
  struct node *prev;
  struct node *next;
} Node;

/* functions */
Node *initialize(void);
void insertNextTo(Node *x, int in_key);
Node *searchNodeByKey(Node *x, int key);
void deleteKey(Node *x, int del_key);
void print_list(Node *x);

/* main */
int main(void) {
  Node *sentinel_node;
  Node *tmp; /* For assignment 4.2 */
  int num;
  char str[STR_MAX];
  sentinel_node = initialize();
  while(1) {
    puts("Enter the operation number.");
    printf("1. Insert, 2. Delete, 3. Print, 4. Exit: ");
    fgets(str, sizeof(str), stdin);
    num = atoi(str); /* */
    /* */
    switch(num) {
    case 1:
      printf("Input a key to insert: ");
      fgets(str, sizeof(str), stdin);
      num = atoi(str);
      /* assignment 4.2 */
      insertNextTo(sentinel_node, num);
      break;
    case 2:
      printf("Input a key to delete: ");
      fgets(str, sizeof(str), stdin);
      num = atoi(str);
      deleteKey(sentinel_node, num);
      break;
    case 3: print_list(sentinel_node);
      break;
    case 4: exit(0);
    default: puts("A wrong key.");
    }
  }
  return 0;
}

Node *initialize(void) {
  Node *x;
  if ((x = (Node *)malloc(sizeof(Node))) == NULL) {
    puts("No resource remained.");
    exit(1);
  }
  x->prev = x;
  x->next = x;
  return x;
}

void insertNextTo(Node *x, int in_key) {
  Node *ins;
  ins = initialize();
  /* */
  ins->key = in_key;
  ins->prev = x;
  ins->next = x->next;
  /* */
  x->next->prev = ins;
  x->next = ins;
}

/* x should be sentinel_node */
Node *searchNodeByKey(Node *x, int key) {
  Node *search = x->next; // the target for deletion
  // stop looping if the search is <x> or the target
  while(!(search == x || search->key == key)) {
    search = search->next;
  }
  return search;
}

/* x should be sentinel_node */
void deleteKey(Node *x, int del_key) {
  Node *search = searchNodeByKey(x, del_key);
  if (search == x) {
    printf("%d is not found.\n", del_key);
  } else {
    search->prev->next = search->next;
    search->next->prev = search->prev;
    free(search);
  }
}

/* x should be sentinel_node */
void print_list(Node *x) {
  Node *print = x->next;
  if (x->next == x) {
    puts("No data found.");
  } else {
    while(print != x) {
      printf("%d ", print->key);
      print = print->next;
    }
    putchar('\n');
  }
}
