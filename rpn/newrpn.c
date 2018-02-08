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

    while(read != EOF) {

        if (valid_num(read)) {
            if (valid_num(old)) {
                val = val*10 + read - '0';
                stack[stacksize-1] = val;
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

    }

}
