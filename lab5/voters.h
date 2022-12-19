#include <stdio.h>

typedef char station_t[7];
typedef struct {
    char *name;
    station_t station;
    int age;
} Voter;

void fprint_voter(FILE *const stream, Voter voter);
int sscanf_voter(char *str, Voter *voter);

typedef enum {
    voter_name,
    voter_station,
    voter_age,
    voter_field_count
} voter_field;

voter_field str2field(char *str);

typedef int cmp_func_t(Voter *, Voter *);
cmp_func_t *field2cmp(voter_field field);

#define VECTOR_ITEM Voter
#define VECTOR_ITEM_DESTRUCTOR(item) free(item.name)
#include "vector.h"

typedef Vector Voters;
