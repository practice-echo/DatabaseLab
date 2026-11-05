#include "virus.h"
#include <stdio.h>

int main(void)
{
    int n = virus_detect_stream(stdin, stdout);
    if (n < 0) {
        fprintf(stderr, "处理输入时出错\n");
        return 1;
    }
    return 0;
}