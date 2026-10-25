#include <stdio.h>
#include <stdlib.h>
#include "create_list.h"
#include "count_books.h"
#include "average_price.h" 
#include "adjust_price.h"
#include "find_max_price.h"
#include "insert_book.h"
#include "delete_book.h"
#include "remove_duplicates.h"

#ifdef _WIN32
#include <windows.h>
#endif

void PrintBooks(LinkList head)
{
    LinkList p;
    for (p = head; p != NULL; p = p->next)
    {
        printf("%s %s %.2f\n", p->data.no, p->data.name, p->data.price);
    }
}

int main(void)
{

#ifdef _WIN32
    SetConsoleOutputCP(65001);   // 输出用 UTF-8
    SetConsoleCP(65001);         // 输入也用 UTF-8
#endif

    int choice;

    printf("请选择操作：\n");
    printf("1. 创建和输出\n");
    printf("2. 价格批量修改\n");
    printf("3. 查找最贵的图书\n");
    printf("4. 新书入库\n");
    printf("5. 旧书出库\n");
    printf("6. 图书去重\n");
    printf("请输入选项: ");
    scanf("%d", &choice);

    printf("请输入图书数据:\n");
    LinkList head = CreateListFromInput();
    int count = CountBooks(head);

        switch (choice)
    {
        case 1:
            printf("%d\n", count);
            PrintBooks(head);
            break;

        case 2:
            printf("%.2f\n", CalculateAveragePrice(head));
            printf("%d\n", count);
            AdjustPrices(head);
            PrintBooks(head);
            break;

        case 3:
            PrintMaxPriceBooks(head);
            break;

        case 4:
            if (HandleInsertInput(&head)) 
            {
                printf("%d\n", CountBooks(head));
                PrintBooks(head);
            }
            break;

        case 5:
        {
            int pos;
            if (scanf("%d", &pos) == 1)
            {
                // 判断位置合法性：1 到 count 之间
                if (pos < 1 || pos > count)
                {
                    printf("抱歉，出库位置非法!\n");
                }
                else
                {
                    DeleteBook(&head, pos);
                    printf("%d\n", CountBooks(head));
                    PrintBooks(head);
                }
            }
            break;
        }

        case 6:
            RemoveDuplicates(head);
            printf("%d\n", CountBooks(head));
            PrintBooks(head);
            break;

        default:
            printf("0");
            break;
    }

        while (head != NULL) 
    {
        LinkList t = head;
        head = head->next;
        free(t);
    }

    return 0;
}