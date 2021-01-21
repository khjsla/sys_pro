#include <stdio.h>
#include <string.h>

int main() {
	int i = 0;
    int j = 0;
	char *x[100];

    for (;;) {
		printf("enter\n");
		scanf("%s", x[i]);
		if (strcmp(x[i], "end")) {
			for (j = 0; j < i; j++) {
				printf("%s", x[j]);
		     }
			break;
		}
		i++;
	}
}

