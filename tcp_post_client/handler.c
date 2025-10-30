#include "handler.h"
#include <stdio.h>
#include <string.h>


void print_handler(const char *data) {
    printf("%s", data);
}


void count_handler(const char *data) {
    static int total = 0;
    total += strlen(data);
    printf("[Mottog %zu byte, totalt %d byte]\n", strlen(data), total);
}
