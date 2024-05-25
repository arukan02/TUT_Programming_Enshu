/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* define */
#define MAX 10
/* structure */
typedef struct stack {
  double array[MAX];
  int counter;
} Stack;
/* functions */
void read_rpn(void);
void push(Stack *x, double n);
double pop(Stack *x);

/* main */
int main(void) {
  read_rpn();
  return 0;
}

/* four basic arithmetic operations on positive real numbers */
void read_rpn(void) {
  Stack x;
  int ch;
  double num1, num2;
  x.counter = 0;
  printf("Enter an equation in Reverse Polish Notation: "); //the input should be 10 2 4 * - 3 + 4 2 - /
  while((ch = getchar()) != EOF) {
    if (isdigit(ch)) { // the token is a digit
      // convert a character code to a number
      ungetc(ch, stdin);
      scanf("%lf", &num1);
      push(&x, num1);
    } else { // the token is not a digit
      switch(ch) {
      case '+':
        num2 = pop(&x); num1 = pop(&x);
        push(&x, num1 + num2);
        break;
      case '-':
        num2 = pop(&x); num1 = pop(&x);
        push(&x, num1 - num2);
        break;
      case '*':
        num2 = pop(&x); num1 = pop(&x);
        push(&x, num1 * num2);
        break;
      case '/':
        num2 = pop(&x); num1 = pop(&x);
        push(&x, num1 / num2);
        break;
      case ' ': break;
      case '\n':
        if (x.counter <= 1) {
          printf("Answer: %.15f\n", pop(&x));
          exit(0);
        } else {
          puts("Stack is not empty.");
          exit(1);
        }
      default:
        puts("Wrong characters entered.");
        exit(1);
      }
    }
  }
}

void push(Stack *x, double n)
{
  if(x->counter < MAX){
    x->array[x->counter] = n;
    x->counter++;
  }
  else {
    printf("Stack Overflow!");
    exit(0);
  }
}

double pop(Stack *x)
{
  if(x->counter > 0){
    x->counter--;
    return x->array[x->counter];
  }
  else {
    printf("Stack Underflow!");
    exit(1);
  }
}