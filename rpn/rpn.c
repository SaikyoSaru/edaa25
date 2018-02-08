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
	int* stack = malloc(10*sizeof(int));
	int read, old, line, val, size, error, d;
	line = error = val = d = 0;

	while (1) {
		read = old = size = 0;
		line++;
		read = getchar();

		while (read != '\0') {
			if (read == EOF ) {
				free(stack);
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
						goto end;
					}
				}

			}

			if (valid_func(read)) {
				if (size < 2) {
					printf("line %d: error at %c\n", line, read);
					old = read;
					goto end;
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
						goto end;
					}
					stack[size-2] = stack[size-2] / stack[size-1];
					size--;
					break;
				}
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
			end:
			while (read != '\n') {
				read = getchar();
			}
			old = read;
		}

	}
	return 0;
}
