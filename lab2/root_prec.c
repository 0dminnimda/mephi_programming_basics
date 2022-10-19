#include <stdio.h>
#include <math.h>

double root_prec(double a, double n, double precision, int *iters)
{
    double y = a;
    for (int i = 0;; i++)
    {
        double new_y = ((n - 1) * y + a / pow(y, n - 1)) / n;
        if ((y - new_y) < precision)
        {
            *iters = i;
            return new_y;
        }
        y = new_y;
    }
}

int guard(int scanf_result)
{
    if (scanf_result == EOF)
        return -1;
    int result = (scanf_result <= 0);
    char c;
    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (c == EOF)
            return -1;
        result = 1;
    }
    return result;
}

#define SCAN(...)                                     \
    if ((guard_res = guard(scanf(__VA_ARGS__))) == 1) \
    {                                                 \
        printf("Faulty input. Try again!\n\n");       \
        continue;                                     \
    }                                                 \
    else if (guard_res == -1)                         \
    {                                                 \
        printf("Fatal error: EOF\n\n");               \
        return -1;                                    \
    }

int main()
{
    while (1)
    {
        int guard_res = 0;
        printf("Hello! Input two integers: base of the root and number\n");
        double a = 0, n = 0;
        SCAN("%lf %lf", &n, &a);
        printf("Input precision\n");
        double third = 0;
        SCAN("%lf", &third);
        printf("Root [base %.17lf] of %.17lf ", n, a);
        int iters = 0;
        printf("with precision %.17lf = %.17lf ", third, root_prec(a, n, third, &iters));
        printf("and it took %d iterations\n", iters);
        printf("Same calculation with standard root = %.17lf", pow(a, 1 / n));
        return 0;
    }
}
