#include "count_books.h"
#include <stddef.h> 

int CountBooks(LinkList head)
{
    int count = 0;
    LinkList p;

    for (p = head; p != NULL; p = p->next)
        count++;

    return count;
}