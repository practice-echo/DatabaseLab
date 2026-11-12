#include <stdio.h>
#include "process.h"

#define MAX_LEN 4096

int main(void) {
    char s[MAX_LEN];

    while (scanf("%4095s", s) == 1) {
        if (s[0] == '0' && s[1] == '\0') break;
        ProcessOne(s);
    }
    return 0;
}