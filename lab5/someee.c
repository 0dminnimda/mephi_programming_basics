#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef size_t sort_id;

sort_id str_to_sort(char *in) {
    return 0;
}

// typedef struct Atom {
//     int field1;
//     char *field2;
//     long long field3;
// } Atom;

// typedef size_t atom_field_offset;

// atom_field_offset str_to_atom_field(char *in) {
//     return 0;
// }

typedef struct Atom {
    void *data;
    int greater(void *a, void *b);
    void print(void *it);
} Atom;

#define DEFINE_ATOM(name, type, greater, format) \
int name##_greater(void *a_ptr, void *b_ptr) { \
    type a = *(type *)a, b = *(type *)b; \
    return (greater); \
} \
void name##_print(void *it) { \
    printf(format, *(type *)it); \
} \
Item name##_atom(type it) { \
    return .{it, name##_greater, name##_print}; \
}

DEFINE_ATOM(int, int, a > b, "%d")
DEFINE_ATOM(str, char *, strmp(a, b) > 0, "%d")

/*
# 1
    file_in - program will read the data from this file
    file_out - program will write the data to this file
# 2
    array_length - number of elements in the generated array
    array_count - number of arrays to generate
# options
    -r --reverse - reverse the sorting direction (form ascending to descending)
    -k --key - which field to use as a sorting key
    -s --sort - what sorting algorithm to use
*/

typedef struct Options {
    char *file_in;
    char *file_out;

    size_t array_length;
    size_t array_count;

    int reverse;
    // atom_field_offset key;
    size_t atom_index;
    sort_id sort;
} Options;

int main(int argc, char *argv[]) {
    int flags, opt;
    int nsecs, tfnd;

    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "nt:")) != -1) {
        switch (opt) {
            case 'n':
                flags = 1;
                break;
            case 't':
                nsecs = atoi(optarg);
                tfnd = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n", flags, tfnd, nsecs,
           optind);

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    printf("name argument = %s\n", argv[optind]);

    /* Other code omitted */

    exit(EXIT_SUCCESS);
}

#include <getopt.h>
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for exit */

int main(int argc, char *argv[]) {
    int c;
    int digit_optind = 0;

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add", required_argument, 0, 0},
            {"append", no_argument, 0, 0},
            {"delete", required_argument, 0, 0},
            {"verbose", no_argument, 0, 0},
            {"create_vector", required_argument, 0, 'c'},
            {"file", required_argument, 0, 0},
            {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "abc:d:012", long_options, &option_index);
        if (c == -1) break;

        switch (c) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg) printf(" with arg %s", optarg);
                printf("\n");
                break;

            case '0':
            case '1':
            case '2':
                if (digit_optind != 0 && digit_optind != this_option_optind)
                    printf("digits occur in two different argv-elements.\n");
                digit_optind = this_option_optind;
                printf("option %c\n", c);
                break;

            case 'a':
                printf("option a\n");
                break;

            case 'b':
                printf("option b\n");
                break;

            case 'c':
                printf("option c with value '%s'\n", optarg);
                break;

            case 'd':
                printf("option d with value '%s'\n", optarg);
                break;

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    // if (optind < argc) {
    //     printf("non-option ARGV-elements: ");
    //     while (optind < argc) printf("%s ", argv[optind++]);
    //     printf("\n");
    // }

    exit(EXIT_SUCCESS);
}





/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define FIELDS FIELD(int, a, l > r, "%d") FIELD(char*, b, strmp(a, b) > 0, "%s") FIELD(long, c, l > r, "%ld")

typedef struct FuncTable {
    int greater(void *l, void *r);
    void fprint(void *it);
} FuncTable;

typedef struct Type { size_t *offsets; FuncTable *functions; size_t field_count; } Type;

#define FIELD(type, name, greater_expr, format) type name;
typedef struct Instance { Type *type; ITEMS } Instance;
#undef FIELD

#define FIELD(type, name, greater_expr, format) \
static int impl_##name##_greater(void *l_ptr, void *r_ptr) { \
    type l = *(type *)l_ptr, r = *(type *)r_ptr; \
    return greater_expr; \
} \
static void impl_##name##_fprint(void *ptr) { \
    fprintf(format, *(type *)ptr); \
}
FIELDS
#undef FIELD

Type make_type() {
    size_t count = 0;

#define FIELD(type, name, greater_expr, format) count++;
    FIELDS
#undef FIELD

    return (Type){
#define FIELD(type, name, greater_expr, format) sizeof(type),
        {sizeof(Type*), FIELDS},
#undef FIELD

#define FIELD(type, name, greater_expr, format) {impl_##name##_greater, impl_##name##_fprint},
        {FIELDS},
        count
#undef FIELD
    };
}


int main()
{


    if (NULL) {
        printf("hhh\n");
    }
    printf("Hello World");

    return 0;
}
























/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASS_NAME Data
#define FIELDS FIELD(int, a, l > r, "%d") FIELD(char*, b, strcmp(l, r) > 0, "%s") FIELD(long, c, l > r, "%ld")

typedef struct FuncTable {
    int (*greater)(void *l, void *r);
    void (*fprint)(FILE *const stream, void *it);
} FuncTable;

typedef struct Type { size_t *offsets; FuncTable *functions; size_t field_count; } Type;

#define FIELD(type, name, greater_expr, format) type name;
typedef struct CLASS_NAME { FIELDS; Type *type; } CLASS_NAME;
#undef FIELD

#define FIELD(type, name, greater_expr, format) \
static int impl_##CLASS_NAME##_##name##_greater(void *l_ptr, void *r_ptr) { \
    type l = *(type *)l_ptr; \
    type r = *(type *)r_ptr; \
    return greater_expr; \
} \
static void impl_##CLASS_NAME##_##name##_fprint(FILE *const stream, void *ptr) { \
    fprintf(stream, format, *(type *)ptr); \
}
FIELDS
#undef FIELD

static inline Type make___type___() {
#define FIELD(...) + 1;
    size_t count = 0 FIELDS;
#undef FIELD

    size_t *offsets = malloc((count + 1) * sizeof(size_t));
    if (offsets != NULL) {
        size_t offset_count = 0;
        size_t offset = 0;
#define FIELD(type, ...) offsets[offset_count++] = offset; offset += sizeof(type);
        FIELDS
#undef FIELD
        offsets[offset_count] = offset;
    }


    FuncTable *functions = malloc(count * sizeof(FuncTable));
    if (functions != NULL) {
        size_t function_count = 0;
#define FIELD(type, name, ...) functions[function_count++] = (FuncTable){impl_##CLASS_NAME##_##name##_greater, impl_##CLASS_NAME##_##name##_fprint};
        FIELDS
#undef FIELD
    }

    return (Type){offsets, functions, count};
}

#define TYPE_MAKER Type make_##CLASS_NAME##_type() { return make___type___(); }
TYPE_MAKER
#undef TYPE_MAKER

#define MAKE_INSTANCE(type, ...) {__VA_ARGS__, type}

// CLASS_NAME make_##CLASS_NAME() {
// #define FIELD(type, name, greater_expr, format) sizeof(type),
//     return (CLASS_NAME){FIELDS};
// #undef FIELD
// }

#undef FIELDS

int main()
{
    Type DataType = make_Data_type();
    Data data = MAKE_INSTANCE(&DataType, 0, NULL, 0);

    (DataType.functions[0].fprint)(stdout, &data.a);

    if (NULL) {
        printf("hhh\n");
    }
    printf("Hello World");

    return 0;
}



















/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASS_NAME Data
#define FIELDS FIELD(int, a, l > r, "%d") FIELD(char*, b, strcmp(l, r) > 0, "%s") FIELD(long, c, l > r, "%ld")

typedef struct FuncTable {
    int (*greater)(void *l, void *r);
    void (*fprint)(FILE *const stream, void *it);
} FuncTable;

typedef struct Type { size_t *offsets; FuncTable *functions; size_t field_count; } Type;

#define FIELD(type, name, greater_expr, format) type name;
typedef struct CLASS_NAME { FIELDS; Type *type; } CLASS_NAME;
#undef FIELD

#define FIELD(type, name, greater_expr, format) \
static int impl_##CLASS_NAME##_##name##_greater(void *l_ptr, void *r_ptr) { \
    type l = *(type *)l_ptr; \
    type r = *(type *)r_ptr; \
    return greater_expr; \
} \
static void impl_##CLASS_NAME##_##name##_fprint(FILE *const stream, void *ptr) { \
    fprintf(stream, format, *(type *)ptr); \
}
FIELDS
#undef FIELD

static inline size_t count_fields() {
#define FIELD(...) + 1;
    return 0 FIELDS;
#undef FIELD
}

static inline size_t *create_vector_offsets(size_t count) {
    size_t *offsets = malloc((count + 1) * sizeof(size_t));
    if (offsets != NULL) {
        size_t offset_count = 0;
        size_t offset = 0;
#define FIELD(type, ...) offsets[offset_count++] = offset; offset += sizeof(type);
        FIELDS
#undef FIELD
        offsets[offset_count] = offset;
    }
    return offsets;
}

static inline FuncTable *create_vector_functions(size_t count) {
    FuncTable *functions = malloc(count * sizeof(FuncTable));
    if (functions != NULL) {
        size_t function_count = 0;
#define FIELD(type, name, ...) functions[function_count++] = (FuncTable){impl_##CLASS_NAME##_##name##_greater, impl_##CLASS_NAME##_##name##_fprint};
        FIELDS
#undef FIELD
    }
    return functions;
}

#define TYPE_MAKER make_type
Type TYPE_MAKER() {
    size_t count = count_fields();
    return (Type){create_vector_offsets(count), create_vector_functions(count), count};
}
#undef TYPE_MAKER

#define MAKE_INSTANCE(type, ...) {__VA_ARGS__, type}

// CLASS_NAME make_##CLASS_NAME() {
// #define FIELD(type, name, greater_expr, format) sizeof(type),
//     return (CLASS_NAME){FIELDS};
// #undef FIELD
// }

#undef FIELDS

int main()
{
    Type DataType = make_type();
    Data data = MAKE_INSTANCE(&DataType, 0, NULL, 0);

    (DataType.functions[0].fprint)(stdout, &data.a);

    if (NULL) {
        printf("hhh\n");
    }
    printf("Hello World");

    return 0;
}















