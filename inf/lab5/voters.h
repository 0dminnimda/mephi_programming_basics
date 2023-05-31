#include <stdio.h>

typedef char station_t[8];
typedef struct {
    char *name;
    station_t station;
    int age;
} Voter;

#define MAX_NAME_LENGTH 256
#define MAX_VOTER_LINE_LENGTH (MAX_NAME_LENGTH + 64)

#define VOTER_SCAN "%255[^,], %3[a-zA-Z]%1[-]%3[0-9], %d"
#define VOTER_PRINT "%s, %.7s, %d"

#define STATION_NAME(station) station
#define STATION_SEPARATOR(station) (station + 3)
#define STATION_NUMBER(station) (station + 4)
#define STATION_END(station) (station + 7)

void fprint_voter(FILE *const stream, Voter voter);
int fscanf_voter(FILE *const stream, Voter *voter);
int sscanf_voter(char *str, Voter *voter);
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
