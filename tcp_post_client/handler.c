#include "handler.h"
#include <stdio.h>
#include <string.h>

// Skriver ut allt direkt
void print_handler(const char *data) {
    printf("%s", data);
}

// Räknar hur många tecken som mottagits
void count_handler(const char *data) {
    static int total = 0;
    total += strlen(data);
    printf("[Mottog %zu byte, totalt %d byte]\n", strlen(data), total);
}
