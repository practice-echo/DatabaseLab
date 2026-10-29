#include "expression.h"
#include "stack.h"
#include <string.h>
#include <ctype.h>

// 获取运算符索引（摘自你的实验指导书）
int getIndex(char theta) {
    int index = 0;
    switch (theta) {
        case '+': index = 0; break;
        case '-': index = 1; break;
        case '*': index = 2; break;
        case '/': index = 3; break;
        case '(': index = 4; break;
        case ')': index = 5; break;
        case '=': // 将 '=' 视同 '#'
        case '#': index = 6; break;
        default: break;
    }
    return index;
}

// 获取优先级（摘自你的实验指导书）
char getPriority(char theta1, char theta2) {
    const char priority[][7] = {
        { '>', '>', '<', '<', '<', '>', '>' },
        { '>', '>', '<', '<', '<', '>', '>' },
        { '>', '>', '>', '>', '<', '>', '>' },
        { '>', '>', '>', '>', '<', '>', '>' },
        { '<', '<', '<', '<', '<', '=', '0' },
        { '>', '>', '>', '>', '0', '>', '>' },
        { '<', '<', '<', '<', '<', '0', '=' }
    };
    int index1 = getIndex(theta1);
    int index2 = getIndex(theta2);
    return priority[index1][index2];
}

// 计算二元运算：b 是右操作数，a 是左操作数
int Operate(int a, char theta, int b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0; // 简单防除0
    }
    return 0;
}

// 核心求值函数：直接计算中缀表达式
int EvaluateExpression(const char *expr) {
    OptrStack OPTR;
    OpndStack OPND;
    
    InitOptrStack(&OPTR);
    InitOpndStack(&OPND);
    PushOptr(&OPTR, '='); // 栈底元素设为 '='（相当于 PDF 中的 '#'）

    int i = 0;
    int len = strlen(expr);

    while (i < len) {
        char c = expr[i];

        // 1. 忽略空格
        if (c == ' ') {
            i++;
            continue;
        }

        // 2. 如果是数字，执行拼数逻辑（实验要求扩展的功能）
        if (isdigit(c)) {
            int num = 0;
            while (i < len && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0'); // 字符转整数并拼数
                i++;
            }
            PushOpnd(&OPND, num);
            continue; // 注意：拼数结束后 i 已经指向下一位，直接 continue
        }

        // 3. 如果是运算符，比较优先级
        char top;
        GetOptrTop(&OPTR, &top);
        char priority = getPriority(top, c);

        if (priority == '<') {
            // 栈顶优先级低，当前字符入栈
            PushOptr(&OPTR, c);
            i++;
        } 
        else if (priority == '=') {
            // 优先级相等，说明遇到了 "( )" 或 "= ="
            char popChar;
            PopOptr(&OPTR, &popChar); // 弹出栈顶，丢弃左括号或结束符
            i++;
        } 
        else if (priority == '>') {
            // 栈顶优先级高，可以计算
            char theta;
            int a, b;
            PopOptr(&OPTR, &theta);
            PopOpnd(&OPND, &b); // 先出栈的是右操作数
            PopOpnd(&OPND, &a); // 后出栈的是左操作数
            
            int result = Operate(a, theta, b);
            PushOpnd(&OPND, result);
            // 注意：这里不要 i++，因为当前读到的运算符 c 还没处理
        }
    }

    // 最终结果留在操作数栈顶
    int finalResult = 0;
    GetOpndTop(&OPND, &finalResult);
    return finalResult;
}