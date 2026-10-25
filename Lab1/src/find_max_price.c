#include <stdio.h>
#include <stddef.h>
#include "find_max_price.h"

void PrintMaxPriceBooks(LinkList head)
{
    if (head == NULL) 
    {
        printf("0\n");
        return;
    }

    // 1. 第一遍遍历：寻找最大价格
    float max_price = head->data.price;
    LinkList p;
    for (p = head->next; p != NULL; p = p->next)
    {
        if (p->data.price > max_price)
        {
            max_price = p->data.price;
        }
    }

    // 2. 第二遍遍历：统计最高价图书的数量
    int count = 0;
    for (p = head; p != NULL; p = p->next)
    {
        if (p->data.price == max_price) 
        {
            count++;
        }
    }

    // 3. 先输出数量
    printf("%d\n", count);

    // 4. 第三遍遍历：输出具体的图书信息
    for (p = head; p != NULL; p = p->next)
    {
        if (p->data.price == max_price) 
        {
            printf("%s %s %.2f\n", p->data.no, p->data.name, p->data.price);
        }
    }
    
    // 注意：这里千万不要写 return count; 
}