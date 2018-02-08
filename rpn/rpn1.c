#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size);
int error;
typedef struct link_t link_t;

struct link_t {

  link_t *next;
  int data;
};

void *xmalloc(size_t size) {
  void *ptr = malloc(sizeof(size));
  if (ptr == NULL) {
    fprintf(stderr, "Out of memory, exiting\n");
    exit(1);
  }
  return ptr;
}

link_t *new_stack(int data) {
  link_t *head;
  head = xmalloc(data);

  head->next = NULL;
  head->data = data;

  return head;
}

void push(link_t **stack, int data) {
  link_t *node;
  node = new_stack(data);

  node->data = data;
  node->next = *stack;
  *stack = node;
}

int pop(link_t **stack) {
  int value;
  if (*stack == NULL) {
    // fprintf(stderr, "End of stack\n");
    // exit(1);
    // add error handling with print!
    value = 0;
  } else {
    link_t *head = *stack;
    value = head->data;
    *stack = head->next;
    free(head);
  }
  return value;
}

int controller(link_t **stack, int func) {

  int tmp;
  switch (func) {
  case '+':
    return pop(stack) + pop(stack);
  case '*':
    return pop(stack) * pop(stack);
  case '/':
    tmp = pop(stack);
    if (tmp == 0) {
      // fprintf(stderr, "ivalid division\n");
      error = 1;
      // return 0;
      // exit(1); // add erro handling with print
    }
    return pop(stack) / tmp;
  case '-':
    tmp = pop(stack);
    return pop(stack) - tmp;
  }
  return 0;
}

int valid_func(int func) {
  // printf("func:(%c)\n", func);
  switch (func) {
  case '+':
  case '-':
  case '*':
  case '/':
    return 2;
  default:
    // fprintf(stderr, "error at %c\n", func);
    return 0;
    // exit(1);
  }
}

int valid_num(int num) {
  // printf("seg");

  if (num < '0' || num > '9') {
    return 0;
  }
  return 1;
}

#define N (10)

int main(void) {

  int old, tmp, tmp2, stacksize, tmp3, line;

  line = 0;
  error = 0;
  for (;;) {
    line++;

    tmp = getchar();
    if (tmp == EOF) {
      exit(1);
    }
    tmp2 = tmp3 = stacksize = old = 0;
    link_t *stack = NULL;

    while (tmp != '\n') {
      //  printf("incoming: (%c)\n", tmp);
      if (valid_num(tmp)) {
        //  printf("char: %d\n", (tmp - '0'));
        // printf("tester %d\n", tmp2);
        if (stacksize == 10) {
          // printf("stacksize%d\n", stacksize);
          fprintf(stderr, "Line %d error at %c\n", line, tmp);
          error = 1;
          stacksize = 0;
          break;
        }
        tmp2 = tmp2 * 10 + (tmp - '0');
        //  printf("tester %d\n", tmp2);

      } else if (!valid_num(tmp) && valid_num(old)) {
        push(&stack, tmp2);
        stacksize++;
        // printf(" input value: %d\n", tmp2);
        tmp2 = 0;

      } else if (valid_func(tmp)) {
        if (stacksize < 2) {
          fprintf(stderr, "Line %d error at %d\n", line, tmp - '0');
          error = 1;
          break;
        }
        tmp3 = controller(&stack, tmp);
        stacksize--;
        push(&stack, tmp3);
        //  printf("final: %d\n", tmp3);
      }

      old = tmp;
      tmp = getchar();
    }
    if (tmp == '\n' && stacksize == 1) {
      printf("Line %d: %d\n", line, pop(&stack));
    } else if (tmp == '\n' && stacksize != 1) {
      fprintf(stderr, "Line %d error at \\n\n", line);
    }
    tmp3 = 0;
  }
  return 0;
}
