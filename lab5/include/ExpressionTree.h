#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

/* 二叉树结点定义 */
typedef struct BiTreeNode {
    char data;                     /* 数据域：操作数或运算符 */
    struct BiTreeNode *leftChild;  /* 左子树 */
    struct BiTreeNode *rightChild; /* 右子树 */
} BiTreeNode, *BiTree;

/* 根据中缀表达式创建表达式树，expr 形如 "2*(2+5)=" */
BiTree CreateExpressionTree(const char *expr);

/* 后序遍历表达式树求值 */
int EvaluateExpressionTree(BiTree root);

/* 对外简洁接口：创建树 + 求值 + 释放树 */
int EvaluateExpression(const char *expr);

/* 释放表达式树 */
void DestroyTree(BiTree root);

#endif