#include <stdio.h>
#include <math.h>

double root(double a, double n, double third, int is_n_of_iter) {
    double y = a;
    for (int i = 0;; i++) {
        double new_y = ((n - 1) * y + a / pow(y, n - 1)) / n;
        // printf("\n%lf", new_y);
        if (!is_n_of_iter) {
            if ((y - new_y) < third)
                return new_y;
        } else {
            if (i >= third)
                return new_y;
        }
        y = new_y;
    }
}

int main() {
    printf("Hello! Input two integers: base of the root and number\n");
    double a = 0;
    double n = 0;
    scanf("%lf %lf", & n, & a);
    printf("Input eather precision (with digits after decimal point) or number of iterations (simple integer)\n");
    double third = 0;
    scanf("%lf", & third);
    int is_n_of_iter = (double)(long) third == third;
    printf("Root [base %.17g] of %.17g ", n, a);
    if (is_n_of_iter) printf("after %d iterations", (int) third);
    else printf("with precision %.17g", third);
    printf(" = %.17g\n", root(a, n, third, is_n_of_iter));
    return 0;
}
