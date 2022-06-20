//
// Created by morse on 2022/5/13.
//
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%p\t0x%.2x\n", p + i, p[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void *));
}

int main() {
    int a = 255;
    float b = 1.0f;
    int *c = &a;

    show_int(a);

    show_float(b);

    show_pointer(c);

    int x = 0x87654321;
    printf("%x\n", ~0xff ^ x);
    printf("%x\n", 0 ^ x);
    printf("%x\n", (~0x0) ^ x);
    printf("%x\n", ~x);
}