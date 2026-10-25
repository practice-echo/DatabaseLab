#ifndef CREATE_LIST_H
#define CREATE_LIST_H

#include "book.h"

/* 从标准输入读入图书信息，遇到 0 0 0 终止，返回链表头指针 */
LinkList CreateListFromInput(void);

#endif