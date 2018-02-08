#include <stdio.h>
#include <stdlib.h>



#define N	(10)

int valid_num(int val) {

	if (val < '0' || val > '9') {

		return 0;
	} else {
		return 1;
	}
}

int valid_func(int func) {
	switch (func) {
	case '+':
	case '-':
	case '*':
	case '/':
	return 1;
	break;
	default:
	return 0;
	break;
	}
}
int main(void) {
	int stack[10];
	int read, old, line, val, size, error, d;
	line = error = val = d = 0;


	for (;;) {
	read = old = size = 0;
	line++;
	read = getchar();

	while (read != '\0') {
	if (read == EOF ) {
	exit(0);
	}
	if (valid_num(read)) {
	if (valid_num(old)) {
	val = val*10 + read - '0';
	stack[size-1] = val;

	} else {
	val = read-'0';
	stack[size] = val;
	size++;
	if (size > 10) {
	printf("line %d: error at %c\n", line, read);
	error = 1;
	break;
	}
	}

	} else if (valid_num(old)) {
	stack[size-1] = val;
	val = 0;
	}

	if (valid_func(read)) {
	if (size < 2) {
	printf("line %d: error at %c\n", line, read);
	error = 1;
	old = read;
	break;
	}

	switch (read) {
	case '+':
	stack[size-2] = stack[size-2] + stack[size-1];
	size--;
	break;
	case '-':
	stack[size-2] = stack[size-2] - stack[size-1];
	size--;
	break;
	case '*':
	stack[size-2] = stack[size-2] * stack[size-1];
	size--;
	break;
	case '/':
	if (stack[size-1] == 0) {
	printf("line %d: error at %c\n", line, read);
	d = 1;
	error = 1;
	break;
	}
	stack[size-2] = stack[size-2] / stack[size-1];
	size--;
	break;
	}
	}

	if (d) {
		d = 0;
		break;
	}


	if (read == '\n') {
	if (size > 1 || size < 1) {
	printf("line %d: error at \\n\n",line);
	break;
	}
	printf("line %d: %d\n", line, stack[size-1]);
	break;
	}
	old = read;
	read = getchar();
	if (!valid_num(old) && !valid_func(old) && old != ' ') {
	printf("line %d: error at %c\n", line, old);
	break;
	}

	}
	if (error) {
	while (read != '\n') {
	read = getchar();
	}
	error = 0;
	old = read;
	}
	}
	return 0;
}
