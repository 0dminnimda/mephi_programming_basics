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

#define MAX_NAME_LENGTH 256
#define VOTER_SCAN "%255[^,], %7s, %d"
#define VOTER_PRINT "%s, %s, %d"

void fprint_voter(FILE *const stream, Voter voter) {
    fprintf(stream, VOTER_PRINT, voter.name, voter.station, voter.age);
}

#define MAX_LINE_LENGTH (MAX_NAME_LENGTH + 64)

int fscanf_voter(FILE *const stream, Voter *voter) {
    voter->name = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (voter->name == NULL) return 1;

    char line[MAX_LINE_LENGTH];
    if (fgets(line, MAX_LINE_LENGTH, stream) == NULL) return 1;

    int res =
        sscanf(line, VOTER_SCAN, voter->name, voter->station, &voter->age);
    return res != 3;
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
