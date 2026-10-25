#include <stddef.h>
#include "adjust_price.h"
#include "average_price.h"

void AdjustPrices(LinkList head)
{
    if (head == NULL) return;

    // 先获取均价
    float avg = CalculateAveragePrice(head);
    LinkList p;

    // 遍历修改价格
    for (p = head; p != NULL; p = p->next)
    {
        if (p->data.price < avg)
        {
            p->data.price = p->data.price * 1.20f; // 涨价 20%
        }
        else
        {
            p->data.price = p->data.price * 1.10f; // 涨价 10%
        }
    }
}