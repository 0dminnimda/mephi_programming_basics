#include "voters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR(x) #x

voter_field str2field(char *str) {
    if (strcmp(str, "name") == 0) return voter_name;
    if (strcmp(str, "station") == 0) return voter_station;
    if (strcmp(str, "age") == 0) return voter_age;
    return voter_field_count;
}

char *field2str(voter_field field) {
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

#define MAKE_STRUCT_CMP(structure, type, name, greater_expr)    \
    static int STRUCT_CMP(structure, name)(structure * l_ptr,   \
                                           structure * r_ptr) { \
        type l = l_ptr->name;                                   \
        type r = r_ptr->name;                                   \
        return greater_expr;                                    \
    }

MAKE_STRUCT_CMP(Voter, char *, name, strcmp(l, r) > 0)
MAKE_STRUCT_CMP(Voter, station_t, station, strcmp(l, r) > 0)
MAKE_STRUCT_CMP(Voter, int, age, l > r)

cmp_func_t *field2cmp(voter_field field) {
    if (field == voter_name) return STRUCT_CMP(Voter, name);
    if (field == voter_station) return STRUCT_CMP(Voter, station);
    return STRUCT_CMP(Voter, age);
}
