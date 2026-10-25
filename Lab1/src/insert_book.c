#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insert_book.h"
#include "count_books.h" // 需要用到 CountBooks 判断长度

LinkList InsertBook(LinkList head, int pos, Book new_book)
{
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s == NULL) return head;
    s->data = new_book;
    s->next = NULL;

    if (pos <= 1 || head == NULL)
    {
        s->next = head;
        return s;
    }

    LNode *p = head;
    int i = 1;
    while (p != NULL && i < pos - 1)
    {
        p = p->next;
        i++;
    }

    if (p != NULL)
    {
        s->next = p->next;
        p->next = s;
    }
    else
    {
        p = head;
        while (p->next != NULL) p = p->next;
        p->next = s;
    }
    return head;
}

// 【新增】封装读取和判断逻辑
int HandleInsertInput(LinkList *head)
{
    int pos;
    if (scanf("%d", &pos) != 1) return 0; // 读取位置
    
    // 吃掉换行符
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char line[256];
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    line[strcspn(line, "\r\n")] = '\0'; // 去掉换行
    
    Book new_book;
    char *last_space = strrchr(line, ' ');
    char *first_space = strchr(line, ' ');
    
    // 如果解析失败，返回0
    if (last_space == NULL || first_space == NULL) return 0;

    *last_space = '\0';
    new_book.price = atof(last_space + 1);
    *first_space = '\0';
    strcpy(new_book.no, line);
    strcpy(new_book.name, first_space + 1);

    // 获取当前长度，判断位置合法性
    int count = CountBooks(*head);
    if (pos < 1 || pos > count + 1)
    {
        printf("抱歉，入库位置非法!\n");
        return 0; // 返回0表示失败
    }

    // 执行插入
    *head = InsertBook(*head, pos, new_book);
    return 1; // 返回1表示成功
}