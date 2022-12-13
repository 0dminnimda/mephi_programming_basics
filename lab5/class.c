#include <stdio.h>

#define ACCESSOR(this, index) (this->content + this->offsets[index])
#define CLASS_OFFSETS CLASS_NAME##_offsets
#define FIELD(index, type, name) type get_##name(Class *this) { return *(type *)ACCESSOR(this, index); } void set_##name(Class *this, type value) { *(type *)ACCESSOR(this, index) = value; } 
#define CLASS(name, ...) make_##name{ size_t offset = 0; __VA_ARGS__ }

// // typedef struct Class {
// //     long long fie;
// //     char af;
// // } Class;

// typedef Class {
//     void *content;
//     size_t *offsets;
// } Class;

// FIELD(long long, fil)

// #define A 5
// #define B A##0

// #define CLASS(name) { #define CLASS_NAME #name }

CLASS(a)

// #undef A

int main()
{
    // Class a;

    // set_fil(&a, 10);

    // printf("Hello World %lld %d %d %d", get_fil(&a), 0b0, 0b10, 0b110);

    printf("Hello World %s", CLASS_NAME);

    return 0;
}


// typedef Class {
//     void *content;
//     offsets
// } Class;

// #define FIELD(type, name) type get_##name(Class this) { return (type)*(this + sizeof(type)); }

