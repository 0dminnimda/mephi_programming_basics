#include "voters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR(x) #x

voter_field str2field(char *str) {
    if (strcmp(str, STR(voter_full_name) + 2) == 0) return voter_full_name;
    if (strcmp(str, STR(voter_station_id) + 2) == 0) return voter_station_id;
    if (strcmp(str, STR(voter_age) + 2) == 0) return voter_age;
    return voter_field_count;
}

#define VOTER_FORMAT "%s, %7s, %d"

void fprint_voter(FILE *const stream, Voter voter) {
    fprint(stream, VOTER_FORMAT, voter.full_name, voter.station_id, voter.age);
}

int sscanf_voter(char *str, Voter *voter) {
    return sscanf(str, VOTER_FORMAT, &voter->full_name, &voter->station_id,
                  &voter->age);
}

#define STRUCT_CMP(structure, name) structure##_##name##_cmp

#define MAKE_STRUCT_CMP(structure, type, name, greater_expr)    \
    static int STRUCT_CMP(structure, name)(structure * l_ptr,   \
                                           structure * r_ptr) { \
        type l = l_ptr->name;                                   \
        type r = r_ptr->name;                                   \
        return greater_expr;                                    \
    }

MAKE_STRUCT_CMP(Voter, char *, full_name, strcmp(l, r) > 0)
MAKE_STRUCT_CMP(Voter, station_t, station_id, strcmp(l, r) > 0)
MAKE_STRUCT_CMP(Voter, int, age, l > r)

cmp_func_t *field2cmp(voter_field field) {
    if (field == voter_full_name) return STRUCT_CMP(Voter, full_name);
    if (field == voter_station_id) return STRUCT_CMP(Voter, station_id);
    return STRUCT_CMP(Voter, age);
}
