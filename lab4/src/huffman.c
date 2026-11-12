#include "huffman.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* 在 ht[1..range] 中选出两个 parent==0 且权值最小的结点 */
static void SelectTwo(const HuffmanTree ht, int range, int *s1, int *s2) {
    int i, minW = INT_MAX;
    *s1 = *s2 = 0;

    for (i = 1; i <= range; ++i) {
        if (ht[i].parent == 0 && ht[i].weight < minW) {
            minW = ht[i].weight;
            *s1 = i;
        }
    }

    minW = INT_MAX;
    for (i = 1; i <= range; ++i) {
        if (i != *s1 && ht[i].parent == 0 && ht[i].weight < minW) {
            minW = ht[i].weight;
            *s2 = i;
        }
    }
}

void Huffman_Init(HuffmanCtx *H, const char *s) {
    int cnt[26] = {0};
    int i, k, m;

    for (i = 0; s[i]; ++i) cnt[s[i] - 'a']++;

    H->n = 0;
    for (i = 0; i < 26; ++i) if (cnt[i] > 0) H->n++;

    m = 2 * H->n - 1;
    H->ht       = (HuffmanTree)calloc(m + 1, sizeof(HTNode));
    H->leafChar = (char *)calloc(H->n + 1, sizeof(char));
    H->code     = (char **)calloc(H->n + 1, sizeof(char *));

    for (i = 0; i < 26; ++i) H->pos[i] = 0;

    k = 1;
    for (i = 0; i < 26; ++i) {
        if (cnt[i] > 0) {
            H->leafChar[k]  = (char)('a' + i);
            H->pos[i]       = k;
            H->ht[k].weight = cnt[i];
            k++;
        }
    }

    for (i = H->n + 1; i <= m; ++i) {
        int s1, s2;
        SelectTwo(H->ht, i - 1, &s1, &s2);
        H->ht[s1].parent = i;
        H->ht[s2].parent = i;
        H->ht[i].lchild  = s1;
        H->ht[i].rchild  = s2;
        H->ht[i].weight  = H->ht[s1].weight + H->ht[s2].weight;
    }
}

void Huffman_Destroy(HuffmanCtx *H) {
    int i;
    if (H->code) {
        for (i = 1; i <= H->n; ++i) free(H->code[i]);
    }
    free(H->code);
    free(H->leafChar);
    free(H->ht);

    H->code = NULL;
    H->leafChar = NULL;
    H->ht = NULL;
    H->n = 0;
}

void Huffman_MakeCodes(HuffmanCtx *H) {
    int i, j;
    char buf[256];

    if (H->n == 1) {                 /* 单字符约定编码为 "0" */
        H->code[1] = (char *)malloc(2);
        H->code[1][0] = '0';
        H->code[1][1] = '\0';
        return;
    }

    for (i = 1; i <= H->n; ++i) {
        int c = i, depth = 0;
        while (H->ht[c].parent != 0) {
            int p = H->ht[c].parent;
            buf[depth++] = (H->ht[p].lchild == c) ? '0' : '1';
            c = p;
        }
        H->code[i] = (char *)malloc(depth + 1);
        for (j = 0; j < depth; ++j)
            H->code[i][j] = buf[depth - 1 - j];   /* 逆序 */
        H->code[i][depth] = '\0';
    }
}

char *Huffman_Encode(const HuffmanCtx *H, const char *s) {
    size_t i, len = strlen(s), total = 0, k = 0;
    char *out;

    if (H->n == 0) {
        out = (char *)malloc(1);
        out[0] = '\0';
        return out;
    }

    for (i = 0; i < len; ++i)
        total += strlen(H->code[H->pos[(unsigned char)s[i] - 'a']]);

    out = (char *)malloc(total + 1);
    for (i = 0; i < len; ++i) {
        const char *c = H->code[H->pos[(unsigned char)s[i] - 'a']];
        size_t l = strlen(c);
        memcpy(out + k, c, l);
        k += l;
    }
    out[k] = '\0';
    return out;
}

char *Huffman_Decode(const HuffmanCtx *H, const char *encoded) {
    size_t i, len = strlen(encoded), k = 0;
    char *out;
    int root, f;

    if (H->n == 0) {
        out = (char *)malloc(1);
        out[0] = '\0';
        return out;
    }

    if (H->n == 1) {                 /* 单字符特殊处理 */
        out = (char *)malloc(len + 1);
        for (i = 0; i < len; ++i) out[i] = H->leafChar[1];
        out[len] = '\0';
        return out;
    }

    out = (char *)malloc(len + 1);
    root = 2 * H->n - 1;
    f = root;
    for (i = 0; i < len; ++i) {
        f = (encoded[i] == '0') ? H->ht[f].lchild : H->ht[f].rchild;
        if (f <= H->n) {
            out[k++] = H->leafChar[f];
            f = root;
        }
    }
    out[k] = '\0';
    return out;
}