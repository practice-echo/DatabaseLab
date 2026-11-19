#include "ExpressionTree.h"

#include <ctype.h>
#include <stdlib.h>

#define MAX_EXPR_LEN 1024

/* ===== 二叉结点指针栈 ===== */
typedef struct {
    BiTree data[MAX_EXPR_LEN];
    int top;
} TreeStack;

static void InitTreeStack(TreeStack *s)          { s->top = -1; }
static int  TreeStackEmpty(TreeStack *s)         { return s->top == -1; }
static void TreeStackPush(TreeStack *s, BiTree t){ s->data[++s->top] = t; }
static BiTree TreeStackPop(TreeStack *s)         { return s->data[s->top--]; }

/* ===== 字符栈 ===== */
typedef struct {
    char data[MAX_EXPR_LEN];
    int top;
} CharStack;

static void InitCharStack(CharStack *s)      { s->top = -1; }
static int  CharStackEmpty(CharStack *s)     { return s->top == -1; }
static void CharStackPush(CharStack *s, char c){ s->data[++s->top] = c; }
static char CharStackPop(CharStack *s)       { return s->data[s->top--]; }
static char CharStackTop(CharStack *s)       { return s->data[s->top]; }

/* ===== 工具函数 ===== */
static int Priority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    }
}

static int IsOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static BiTree MakeNode(char ch, BiTree left, BiTree right) {
    BiTree node = (BiTree)malloc(sizeof(BiTreeNode));
    if (node == NULL) return NULL;
    node->data       = ch;
    node->leftChild  = left;
    node->rightChild = right;
    return node;
}

static int GetValue(char theta, int a, int b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;   /* 实验要求整数除法 */
        default:  return 0;
    }
}

/* ===== 表达式树创建 ===== */
BiTree CreateExpressionTree(const char *expr) {
    TreeStack EXPT;
    CharStack OPTR;
    const char *p;

    InitTreeStack(&EXPT);
    InitCharStack(&OPTR);
    CharStackPush(&OPTR, '#');   /* 起始哨兵 */

    for (p = expr; *p != '\0' && *p != '='; ++p) {
        char ch = *p;

        if (isspace((unsigned char)ch)) continue;

        if (isdigit((unsigned char)ch)) {
            /* 题目要求：数均为小于10的正整数，单字符即为一个操作数 */
            TreeStackPush(&EXPT, MakeNode(ch, NULL, NULL));
        } else if (ch == '(') {
            CharStackPush(&OPTR, ch);
        } else if (ch == ')') {
            while (!CharStackEmpty(&OPTR) && CharStackTop(&OPTR) != '(') {
                char op = CharStackPop(&OPTR);
                BiTree right = TreeStackPop(&EXPT);
                BiTree left  = TreeStackPop(&EXPT);
                TreeStackPush(&EXPT, MakeNode(op, left, right));
            }
            if (!CharStackEmpty(&OPTR) && CharStackTop(&OPTR) == '(') {
                CharStackPop(&OPTR);
            }
        } else if (IsOperator(ch)) {
            while (!CharStackEmpty(&OPTR) &&
                   CharStackTop(&OPTR) != '(' &&
                   CharStackTop(&OPTR) != '#' &&
                   Priority(CharStackTop(&OPTR)) >= Priority(ch)) {
                char op = CharStackPop(&OPTR);
                BiTree right = TreeStackPop(&EXPT);
                BiTree left  = TreeStackPop(&EXPT);
                TreeStackPush(&EXPT, MakeNode(op, left, right));
            }
            CharStackPush(&OPTR, ch);
        }
    }

    /* 处理栈中剩余运算符 */
    while (!CharStackEmpty(&OPTR) && CharStackTop(&OPTR) != '#') {
        char op = CharStackPop(&OPTR);
        BiTree right = TreeStackPop(&EXPT);
        BiTree left  = TreeStackPop(&EXPT);
        TreeStackPush(&EXPT, MakeNode(op, left, right));
    }

    if (TreeStackEmpty(&EXPT)) return NULL;
    return TreeStackPop(&EXPT);
}

/* ===== 后序遍历求值 ===== */
int EvaluateExpressionTree(BiTree root) {
    int a, b;
    if (root == NULL) return 0;

    /* 叶子结点是操作数 */
    if (root->leftChild == NULL && root->rightChild == NULL) {
        return root->data - '0';
    }

    a = EvaluateExpressionTree(root->leftChild);
    b = EvaluateExpressionTree(root->rightChild);
    return GetValue(root->data, a, b);
}

/* ===== 对外接口 ===== */
int EvaluateExpression(const char *expr) {
    BiTree root = CreateExpressionTree(expr);
    int value   = EvaluateExpressionTree(root);
    DestroyTree(root);
    return value;
}

void DestroyTree(BiTree root) {
    if (root == NULL) return;
    DestroyTree(root->leftChild);
    DestroyTree(root->rightChild);
    free(root);
}