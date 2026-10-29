#include "stack.h"

/* ================== 操作数栈 (OPND) 实现 ================== */

void InitOpndStack(OpndStack *S) {
    S->top = -1;
}

int IsOpndEmpty(OpndStack *S) {
    return S->top == -1;
}

int PushOpnd(OpndStack *S, int e) {
    if (S->top >= MAXSIZE - 1) {
        return 0; // 栈满
    }
    S->top++;
    S->data[S->top] = e;
    return 1;
}

int PopOpnd(OpndStack *S, int *e) {
    if (IsOpndEmpty(S)) {
        return 0; // 栈空
    }
    *e = S->data[S->top];
    S->top--;
    return 1;
}

int GetOpndTop(OpndStack *S, int *e) {
    if (IsOpndEmpty(S)) {
        return 0; // 栈空
    }
    *e = S->data[S->top];
    return 1;
}


/* ================== 运算符栈 (OPTR) 实现 ================== */

void InitOptrStack(OptrStack *S) {
    S->top = -1;
}

int IsOptrEmpty(OptrStack *S) {
    return S->top == -1;
}

int PushOptr(OptrStack *S, char e) {
    if (S->top >= MAXSIZE - 1) {
        return 0; // 栈满
    }
    S->top++;
    S->data[S->top] = e;
    return 1;
}

int PopOptr(OptrStack *S, char *e) {
    if (IsOptrEmpty(S)) {
        return 0; // 栈空
    }
    *e = S->data[S->top];
    S->top--;
    return 1;
}

int GetOptrTop(OptrStack *S, char *e) {
    if (IsOptrEmpty(S)) {
        return 0; // 栈空
    }
    *e = S->data[S->top];
    return 1;
}