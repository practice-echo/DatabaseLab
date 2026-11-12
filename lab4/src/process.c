#include "process.h"
#include "huffman.h"
#include "printer.h"
#include <stdio.h>
#include <stdlib.h>

void ProcessOne(const char *s) {
    HuffmanCtx H;
    char *encoded, *decoded;

    Huffman_Init(&H, s);
    Huffman_MakeCodes(&H);

    encoded = Huffman_Encode(&H, s);
    decoded = Huffman_Decode(&H, encoded);

    PrintFrequency(&H);
    PrintTree(&H);
    PrintCodes(&H);
    printf("%s\n", encoded);
    printf("%s\n", decoded);

    free(encoded);
    free(decoded);
    Huffman_Destroy(&H);
}