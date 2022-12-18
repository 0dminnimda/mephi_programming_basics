#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSETOF(type, field) ((size_t)&(((type *)0)->field))
#define FIELD_AT(obj, index) (obj + obj->type->offsets[index])
#define FUNCS_AT(obj, index) (obj->type->functions[index])

typedef struct Object Object;

typedef struct FuncTable {
    int (*greater)(Object *l, Object *r);
    void (*fprint)(FILE *const stream, Object *it);
} FuncTable;

typedef struct Type {
    char **names;
    size_t *offsets;
    FuncTable *functions;
    size_t field_count;
} Type;

#define OBJECT_FIELDS Type *type;
typedef struct Object { OBJECT_FIELDS; } Object;

void fpint(FILE *const stream, Object *obj, size_t index) {
    FUNCS_AT(obj, index).fprint(stream, FIELD_AT(obj, index));
}

int greater(Object *lhs, Object *rhs, size_t index) {
    if (lhs->type != rhs->type) return 0;
    FUNCS_AT(lhs, index).greater(FIELD_AT(lhs, index), FIELD_AT(rhs, index));
}

size_t offset_of(Object *obj, char *name) {
    for (size_t result = 0; result < obj->type->field_count; result++) {
        if (strcmp(obj->type->names[result], name) == 0) {
            return result;
        }
    }
    return -1;
}


#define CLASS_NAME Data
#define FIELDS FIELD(int, a, l > r, "%d") FIELD(char*, b, strcmp(l, r) > 0, "%s") FIELD(long, c, l > r, "%ld")

#define FIELD(type, name, greater_expr, format) type name;
typedef struct CLASS_NAME { OBJECT_FIELDS; FIELDS; } CLASS_NAME;
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
#undef TYPE_MAKER

#undef FIELDS

int main()
{
    //printf("%s\n", STR(impl_##CLASS_NAME##_##name##_greater));
    Type DataType = make_type();
    // char **name = {"a", "b", "c"};
    // size_t *offsets = {OFFSETOF(CLASS_NAME, a), OFFSETOF(CLASS_NAME, b), OFFSETOF(CLASS_NAME, c)};
    // FuncTable *funcs = {
    //     (FuncTable){impl_Data_a_greater, impl_Data_a_fprint},
    //     (FuncTable){impl_Data_b_greater, impl_Data_b_fprint},
    //     (FuncTable){impl_Data_c_greater, impl_Data_c_fprint},
    // };
    // Type DataType = {
    //     name,
    //     offsets,
    //     funcs,
    //     3
    // };
    Data o_data1 = {&DataType, 4, "dsdfgdf", 0};
    Data o_data2 = {&DataType, 3, "", 123};
    Object *data1 = (Object *)&o_data1;
    Object *data2 = (Object *)&o_data2;

    printf("a -> %zu, b -> %zu, c -> %zu\n", offset_of(data1, "a"), offset_of(data1, "b"), offset_of(data1, "c"));

    fpint(stdout, data1, 0); printf(" > "); fpint(stdout, data2, 0); printf(" = %d\n", greater(data1, data2, 0)); 
    printf("'"); fpint(stdout, data1, 1); printf("' > '"); fpint(stdout, data2, 1); printf("' = %d\n", greater(data1, data2, 1)); 
    fpint(stdout, data1, 2); printf(" > "); fpint(stdout, data2, 2); printf(" = %d\n", greater(data1, data2, 2)); 


    return 0;
}
