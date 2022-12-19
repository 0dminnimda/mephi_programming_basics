#include "voters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR(x) #x

field_t str2field(char *str) {
    if (strcmp(str, "name") == 0) return voter_name;
    if (strcmp(str, "station") == 0) return voter_station;
    if (strcmp(str, "age") == 0) return voter_age;
    return voter_field_count;
}

char *field2str(field_t field) {
    if (field == voter_name) return "name";
    if (field == voter_station) return "station";
    if (field == voter_age) return "age";
    return "invalid-field";
}

#define VOTER_FORMAT "%s, %7s, %d"

void fprint_voter(FILE *const stream, Voter voter) {
    fprintf(stream, VOTER_FORMAT, voter.name, voter.station, voter.age);
}

int sscanf_voter(char *str, Voter *voter) {
    return sscanf(str, VOTER_FORMAT, voter->name, voter->station, &voter->age);
}

#define STRUCT_CMP(structure, name) structure##_##name##_cmp
#define MAKE_STRUCT_CMP(structure, name, cmp)                   \
    static int STRUCT_CMP(structure, name)(structure * l_ptr,   \
                                           structure * r_ptr) { \
        return cmp(l_ptr->name, r_ptr->name);                   \
    }

#define DEFAULT_CMP(l, r) ((l > r) - (l < r))

MAKE_STRUCT_CMP(Voter, name, strcmp)
MAKE_STRUCT_CMP(Voter, station, strcmp)
MAKE_STRUCT_CMP(Voter, age, DEFAULT_CMP)

cmp_func_t *field2cmp(field_t field) {
    if (field == voter_name) return STRUCT_CMP(Voter, name);
    if (field == voter_station) return STRUCT_CMP(Voter, station);
    return STRUCT_CMP(Voter, age);
}
