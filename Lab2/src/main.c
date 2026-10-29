#include <stdio.h>
#include <string.h>
#include "expression.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    char expr[1024]; // 假设每行表达式不超过 1024 字符

    #ifdef _WIN32
    SetConsoleOutputCP(65001);   // 输出用 UTF-8
    SetConsoleCP(65001);         // 输入也用 UTF-8
    #endif

    printf("请输入表达式(输入单独“=”终止):\n");

    // 循环读取每一行
    while (fgets(expr, sizeof(expr), stdin) != NULL) {
        // 去除 fgets 读入的换行符
        expr[strcspn(expr, "\r\n")] = '\0';

        // 判断结束条件：如果只有一个 '='，程序结束
        if (strcmp(expr, "=") == 0) {
            break;
        }

        // 调用封装好的求值函数，直接打印结果
        int result = EvaluateExpression(expr);
        printf("%d\n", result);
    }

    return 0;
}