#include <stddef.h>
#include "average_price.h"
#include "count_books.h"  // 复用统计数量的函数

float CalculateAveragePrice(LinkList head)
{
    int count = CountBooks(head);
    if (count == 0) 
    {
        return 0.0f; // 防止除以 0 导致崩溃
    }

    float total_price = 0.0f;
    LinkList p;
    
    // 遍历累加价格
    for (p = head; p != NULL; p = p->next)
    {
        total_price += p->data.price;
    }

    return total_price / count;
}