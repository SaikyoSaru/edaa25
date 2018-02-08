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
      //fprintf(stderr, "ivalid division\n");
      error = 1;
      //return 0;
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
  int read, val, stacksize, line;


  for(;;) {
    read = getchar();
    list_t* stack = NULL;
    stacksize = read = val = line = 0;

    while(read != EOF && read != '\n') {
      line++;

      if (valid(read)) {

        if (stacksize == 10 ) {
          fprintf(fprintf, "Line %d error at %c\n"line, read);
          break;
        }
        


      }



    }


  }

  return 0;
}
