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

void fprint_voter(FILE *const stream, Voter voter) {
    fprintf(stream, VOTER_PRINT, voter.name, voter.station, voter.age);
}

int fscanf_voter(FILE *const stream, Voter *voter) {
    char line[MAX_VOTER_LINE_LENGTH];
    if (fgets(line, MAX_VOTER_LINE_LENGTH, stream) == NULL) return 1;
    return sscanf_voter(line, voter);
}

#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGITS "0123456789"
// #define IS_LETTER(x) ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z')

int sscanf_voter(char *str, Voter *voter) {
    voter->name = malloc(MAX_VOTER_LINE_LENGTH * sizeof(char));
    if (voter->name == NULL) return 1;

    int ok = sscanf(str, VOTER_SCAN, voter->name, STATION_NAME(voter->station),
                    STATION_SEPARATOR(voter->station),
                    STATION_NUMBER(voter->station), &voter->age) == 5;
    *STATION_END(voter->station) = '\0';
    ok = ok && strspn(STATION_NAME(voter->station), LETTERS) == 3;
    ok = ok && strspn(STATION_NUMBER(voter->station), DIGITS) == 3;
    return !ok;
}

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

#define ALPHABET(x) x, NELEMS(x)

char *rand_string(char *str, size_t size, const char *alphabet,
                  size_t alphabet_size) {
    while (size--) {
        int key = rand() % (int)(alphabet_size - 1);
        str[size] = alphabet[key];
    }
    return str;
}

int make_fake_voter(Voter *voter) {
    voter->name = malloc(MAX_VOTER_LINE_LENGTH * sizeof(char));
    if (voter->name == NULL) return 1;

    int len = rand() % (MAX_VOTER_LINE_LENGTH / 4);
    rand_string(voter->name, len, ALPHABET(LETTERS DIGITS ".-#'?! "));
    voter->name[len] = '\0';

    rand_string(STATION_NAME(voter->station), 3, ALPHABET(LETTERS));
    *STATION_SEPARATOR(voter->station) = '-';
    rand_string(STATION_NUMBER(voter->station), 3, ALPHABET(DIGITS));
    *STATION_END(voter->station) = '\0';

    voter->age = rand() % 200;

    return 0;
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
