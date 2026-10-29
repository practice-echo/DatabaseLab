#ifndef STACK_H
#define STACK_H

#define MAXSIZE 100 // 栈的最大容量

/* ================== 操作数栈 (OPND) ================== */
typedef struct {
    int data[MAXSIZE];
    int top;
} OpndStack;

// 初始化操作数栈
void InitOpndStack(OpndStack *S);
// 判断操作数栈是否为空
int IsOpndEmpty(OpndStack *S);
// 进栈（操作数）
int PushOpnd(OpndStack *S, int e);
// 出栈（操作数）
int PopOpnd(OpndStack *S, int *e);
// 取栈顶元素（操作数）
int GetOpndTop(OpndStack *S, int *e);


/* ================== 运算符栈 (OPTR) ================== */
typedef struct {
    char data[MAXSIZE];
    int top;
} OptrStack;

// 初始化运算符栈
void InitOptrStack(OptrStack *S);
// 判断运算符栈是否为空
int IsOptrEmpty(OptrStack *S);
// 进栈（运算符）
int PushOptr(OptrStack *S, char e);
// 出栈（运算符）
int PopOptr(OptrStack *S, char *e);
// 取栈顶元素（运算符）
int GetOptrTop(OptrStack *S, char *e);

#endif // STACK_H