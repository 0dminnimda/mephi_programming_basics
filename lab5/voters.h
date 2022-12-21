#include <stdio.h>

typedef char station_t[7];
typedef struct {
    char *name;
    station_t station;
    int age;
} Voter;

void fprint_voter(FILE *const stream, Voter voter);
int fscanf_voter(FILE *const stream, Voter *voter);
int make_fake_voter(Voter *voter);

typedef enum {
    voter_name,
    voter_station,
    voter_age,
    voter_field_count
} field_t;

field_t str2field(char *str);
char *field2str(field_t field);

typedef int cmp_func_t(Voter *, Voter *);
cmp_func_t *field2cmp(field_t field);

#define VECTOR_ITEM Voter
#define VECTOR_ITEM_DESTRUCTOR(item) free(item.name)
#include "vector.h"

typedef Vector Voters;
