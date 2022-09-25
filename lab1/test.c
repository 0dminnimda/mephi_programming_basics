#include <stdio.h>
#include <math.h>

int maximize(int n) {
	int size = ceil(log10(n));
	int sorted = 0;
	while (sorted != 1) {
		sorted = 1;
		int offset = 1;
		for (int i = 0; i < size - 1; i++) {
			int digit1 = n / (offset*10) % 10;
			int digit2 = n / (offset   ) % 10;
			if (digit1 > digit2) {
				n = n - digit1 * offset * 10 + digit2 * offset * 10;
				n = n - digit2 * offset      + digit1 * offset     ;
				sorted = 0;
			}
			offset *= 10;
		}
	}
	return n;
}

int main() {
	printf("Hello! Input one integer\n");
	int n = 0;
	scanf("%d", &n);
	if (n > 0)
		printf("Minimal digit combination: %d (leading zeros are not shown)\n", maximize(n));
	else
		printf("It's not an integer ;(\nSorry, but you'll have to enter an integer next time!\n");
	return 0;
}
