#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remove_duplicates.h"

void RemoveDuplicates(LinkList head)
{
    if (head == NULL) return;

    LinkList p = head;
    while (p != NULL)
    {
        LinkList q = p;
        // 在 p 之后的链表中寻找是否有重复的 ISBN
        while (q->next != NULL)
        {
            if (strcmp(q->next->data.no, p->data.no) == 0)
            {
                // 发现重复，删除 q->next
                LinkList temp = q->next;
                q->next = temp->next;
                free(temp);
            }
            else
            {
                q = q->next;
            }
        }
        p = p->next;
    }
}