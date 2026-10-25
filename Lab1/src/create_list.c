#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_list.h"

LinkList CreateListFromInput(void)
{
    LinkList head = NULL, tail = NULL;
    char line[256];

    while (fgets(line, sizeof(line), stdin))
    {
        char no[20], name[50];
        float price;
        char *first_space, *last_space;

        line[strcspn(line, "\r\n")] = '\0';

        last_space = strrchr(line, ' ');
        if (last_space == NULL)
            continue;
        *last_space = '\0';
        price = atof(last_space + 1);

        first_space = strchr(line, ' ');
        if (first_space == NULL)
            continue;
        *first_space = '\0';

        strncpy(no, line, sizeof(no) - 1);
        no[sizeof(no) - 1] = '\0';

        strncpy(name, first_space + 1, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';

        if (strcmp(no, "0") == 0 && strcmp(name, "0") == 0 && price == 0)
            break;

        LNode *s = (LNode *)malloc(sizeof(LNode));
        if (s == NULL)
            return head;

        strcpy(s->data.no, no);
        strcpy(s->data.name, name);
        s->data.price = price;
        s->next = NULL;

        if (head == NULL)
            head = tail = s;
        else
        {
            tail->next = s;
            tail = s;
        }
    }

    return head;
}