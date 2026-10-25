#ifndef BOOK_H
#define BOOK_H

typedef struct            // 图书信息定义
{
    char no[20];          // 图书 ISBN
    char name[50];        // 图书名字
    float price;          // 图书价格
} Book;

typedef struct LNode
{
    Book data;            // 结点的数据域
    struct LNode *next;   // 结点的指针域
} LNode, *LinkList;

#endif