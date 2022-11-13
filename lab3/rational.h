typedef struct RationalNode_ *Rational;

int sscan_rational(char *str_ptr, Rational *rat, int *offset);
void destroy_rational(Rational rat);
void print_rational(Rational rat);
