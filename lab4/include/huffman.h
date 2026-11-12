#ifndef HUFFMAN_H
#define HUFFMAN_H

/* 与教材一致：下标 0 不用，结点存于 1..2n-1 */
typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef struct {
    HuffmanTree ht;      /* 下标 1..2n-1 */
    int n;               /* 字符类别数 */
    char *leafChar;      /* 下标 1..n，叶子对应字符 */
    int pos[26];         /* pos[ch - 'a'] = 叶子下标 */
    char **code;         /* 下标 1..n，叶子编码字符串 */
} HuffmanCtx;

/* 统计频率并构造哈夫曼树（含 n==0、n==1 的处理） */
void Huffman_Init(HuffmanCtx *H, const char *s);

/* 释放 HuffmanCtx 内部动态内存 */
void Huffman_Destroy(HuffmanCtx *H);

/* 由哈夫曼树生成每个叶子的编码 */
void Huffman_MakeCodes(HuffmanCtx *H);

/* 编码，返回 malloc 出来的字符串，调用者 free */
char *Huffman_Encode(const HuffmanCtx *H, const char *s);

/* 译码，返回 malloc 出来的字符串，调用者 free */
char *Huffman_Decode(const HuffmanCtx *H, const char *encoded);

#endif