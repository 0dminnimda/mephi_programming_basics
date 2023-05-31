typedef struct RationalNode_ *Rational;

long long get_decimal(Rational rat);
unsigned long long get_fractional(Rational rat);

int sscan_rational(char *str_ptr, Rational *rat, int *offset);
void destroy_rational(Rational rat);
void print_rational(Rational rat);
