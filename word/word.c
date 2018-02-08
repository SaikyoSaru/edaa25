#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
	int read, test_len, size, max;
	read = test_len = max = 0;
	size = 20;
	char* max_word = malloc(size*sizeof(char));
	char* test = malloc(size*sizeof(char));
	while (read != EOF) {
		test_len = 0;
		while (isalpha(read)) {
			test[test_len] = read;
			if (++test_len == size) {
				size += 10;
				test = realloc(test, sizeof(char)*(size));
			}
			read = getchar();
		}
		if ( test_len > max ) {
			max = test_len;
			max_word = realloc(max_word, sizeof(char)*max);
			strcpy(max_word, test);
		}
		read = getchar();
	}
	printf("%d characters in longest word: %s\n", max, max_word);
	free(max_word);
	free(test);
	exit(0);
}
