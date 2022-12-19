#include <stdio.h>

typedef char station_t[7];
typedef struct {
    char *full_name;
    station_t station_id;
    int age;
} Voter;

void fprint_voter(FILE *const stream, Voter voter);
int sscanf_voter(char *str, Voter *voter);

typedef enum {
    voter_full_name,
    voter_station_id,
    voter_age,
    voter_field_count
} voter_field;

voter_field str2field(char *str);

typedef int cmp_func_t(Voter *, Voter *);
cmp_func_t *field2cmp(voter_field field);

#define VECTOR_ITEM Voter
#define VECTOR_ITEM_DESTRUCTOR(item) free(item.full_name)
#include "vector.h"

typedef Vector Voters;
