#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASS_NAME Data
#define FIELDS FIELD(int, a, l > r, "%d") FIELD(char*, b, strcmp(l, r) > 0, "%s") FIELD(long, c, l > r, "%ld")

typedef struct FuncTable {
    int (*greater)(void *l, void *r);
    void (*fprint)(FILE *const stream, void *it);
} FuncTable;

typedef struct Type { char **names; size_t *offsets; FuncTable *functions; size_t field_count; } Type;

#define FIELD(type, name, greater_expr, format) type name;
typedef struct CLASS_NAME { Type *type; FIELDS; } CLASS_NAME;
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

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT)) 

static inline Type make_type() {
    size_t count = 0;

#define FIELD(type, name, greater_expr, format) count++;
    FIELDS
#undef FIELD


    char **names = malloc(count * sizeof(char*));
    if (names != NULL) {
        size_t name_count = 0;
#define FIELD(type, name, ...) names[name_count++] = #name;
        FIELDS
#undef FIELD
    }


    size_t *offsets = malloc(count * sizeof(size_t));
    if (offsets != NULL) {
        size_t offset_count = 0;
#define FIELD(type, name, ...) offsets[offset_count++] = OFFSETOF(CLASS_NAME, name);
        FIELDS
#undef FIELD
    }


    FuncTable *functions = malloc(count * sizeof(FuncTable));
    if (functions != NULL) {
        size_t function_count = 0;
#define FIELD(type, name, ...) functions[function_count++] = (FuncTable){impl_##CLASS_NAME##_##name##_greater, impl_##CLASS_NAME##_##name##_fprint};
        FIELDS
#undef FIELD
    }

    return (Type){names, offsets, functions, count};
}

#define TYPE_MAKER Type make_##CLASS_NAME##_type() { return make_type(); }
TYPE_MAKER

#define MAKE_INSTANCE(type, ...) {__VA_ARGS__, type}

// CLASS_NAME make_##CLASS_NAME() {
// #define FIELD(type, name, greater_expr, format) sizeof(type),
//     return (CLASS_NAME){FIELDS};
// #undef FIELD
// }

#undef FIELDS

#define TYPE(instance) (*(Type **)instance)

void fpint(FILE *const stream, void *instance, size_t index) {
    Type *tp = TYPE(instance);
    tp->functions[index].fprint(stream, instance + tp->offsets[index]);
}

int greater(void *instance_l, void *instance_r, size_t index) {
    Type *tp = TYPE(instance_l);
    if (tp != TYPE(instance_r)) return 0;
    tp->functions[index].greater(instance_l + tp->offsets[index], instance_r + tp->offsets[index]);
}

size_t offset_of(void *instance, char *name) {
    Type *tp = TYPE(instance);

    for (size_t result = 0; result < tp->field_count; result++) {
        if (strcmp(tp->names[result], name) == 0) {
            return result;
        }
    }
    return -1;
}

int main()
{
    Type DataType = make_type();
    Data data1 = {&DataType, 4, "dsdfgdf", 0};
    Data data2 = {&DataType, 3, "", 123};

    // printf("%p %zu\n", &data1.type, sizeof(Type*));
    // printf("%p %zu\n", &data1.a, sizeof(int));
    // printf("%p %zu\n", &data1.b, sizeof(char*));
    // printf("%p %zu\n", &data1.c, sizeof(long));
    // printf("%p\n", DataType.functions[0].fprint);
    // printf("%p\n", DataType.functions[1].fprint);
    // printf("%p\n", DataType.functions[2].fprint);
    // DataType.functions[2].fprint(stdout, &data1.c);

    printf("a -> %zu, b -> %zu, c -> %zu\n", offset_of(&data1, "a"), offset_of(&data1, "b"), offset_of(&data1, "c"));

    fpint(stdout, &data1, 0); printf(" > "); fpint(stdout, &data2, 0); printf(" = %d\n", greater(&data1, &data2, 0)); 
    printf("'"); fpint(stdout, &data1, 1); printf("' > '"); fpint(stdout, &data2, 1); printf("' = %d\n", greater(&data1, &data2, 1)); 
    fpint(stdout, &data1, 2); printf(" > "); fpint(stdout, &data2, 2); printf(" = %d\n", greater(&data1, &data2, 2)); 


    return 0;
}
