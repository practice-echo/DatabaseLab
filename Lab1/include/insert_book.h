#ifndef INSERT_BOOK_H
#define INSERT_BOOK_H

#include "book.h"

/* 执行插入，返回新的头指针 */
LinkList InsertBook(LinkList head, int pos, Book new_book);

/* 负责读取位置、解析新书信息并执行插入，成功返回1，非法返回0 */
int HandleInsertInput(LinkList *head);

#endif