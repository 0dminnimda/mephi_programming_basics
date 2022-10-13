#include <stdio.h>
#include <math.h>

double root_prec(double a, double n, double precision) {
	double y = a;
	for (int i = 0;; i++) {
			double new_y = ((n-1)*y +a/pow(y, n-1)) / n;
			if ((y - new_y) < precision)
				return new_y;
			y = new_y;
	}
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
	    printf("Input eather precision\n");
	    double third = 0;
	    SCAN("%lf", &third);
	    printf("Root [base %.17lf] of %.17lf ", n, a);
	    printf("with precision %.17lf = %.17lf\n", third, root_prec(a, n, third));
	    return 0;
    }
}
