#include "printer.h"
#include <stdio.h>

void PrintFrequency(const HuffmanCtx *H) {
    int i;
    for (i = 1; i <= H->n; ++i) {
        if (i > 1) putchar(' ');
        printf("%c:%d", H->leafChar[i], H->ht[i].weight);
    }
    putchar('\n');
}

void PrintTree(const HuffmanCtx *H) {
    int i, m = 2 * H->n - 1;
    for (i = 1; i <= m; ++i) {
        printf("%d %d %d %d %d\n",
               i,
               H->ht[i].weight,
               H->ht[i].parent,
               H->ht[i].lchild,
               H->ht[i].rchild);
    }
}

void PrintCodes(const HuffmanCtx *H) {
    int i;
    for (i = 1; i <= H->n; ++i) {
        if (i > 1) putchar(' ');
        printf("%c:%s", H->leafChar[i], H->code[i]);
    }
    putchar('\n');
}