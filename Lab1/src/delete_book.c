#include <stdio.h>
#include <stdlib.h>
#include "delete_book.h"

void DeleteBook(LinkList *head, int pos)
{
    if (*head == NULL || pos < 1) return;

    // 如果删除的是头节点
    if (pos == 1)
    {
        LinkList temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    // 查找第 pos-1 个节点
    LinkList p = *head;
    int i = 1;
    while (p != NULL && i < pos - 1)
    {
        p = p->next;
        i++;
    }

    // 如果找到了并且有下一个节点（即要删除的节点存在）
    if (p != NULL && p->next != NULL)
    {
        LinkList temp = p->next;
        p->next = temp->next;
        free(temp);
    }
}