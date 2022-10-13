#include <stdio.h>
#include <math.h>

double root_iter(double a, double n, int num_of_iter) {
	double y = a;
	for (int i = 0; i < num_of_iter; i++) {
			y = ((n-1)*y +a/pow(y, n-1)) / n;
	}
	return y;
}

int guard(int scanf_result) {
	int result = (scanf_result <= 0);
	char c;
	while ((c = getchar()) != '\n' && (c != EOF))
		result = 1;
	return result;
}

#define SCAN(...) if (guard(scanf(__VA_ARGS__))) { printf("Faulty input. Try again!\n\n"); continue; }

int main() {
    while (1) {
	    printf("Hello! Input two integers: base of the root and number\n");
	    double a = 0, n = 0;
	    SCAN("%lf %lf", &n, &a);
	    printf("Input number of iterations\n");
	    int third = 0;
	    SCAN("%d", &third);
	    printf("Root [base %.17lf] of %.17lf ", n, a);
	    printf("after %d iterations  = %.17lf\n", third, root_iter(a, n, third));
	    return 0;
    }
}
