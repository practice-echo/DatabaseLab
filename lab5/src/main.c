#include "ExpressionTree.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    char line[1024];

    while (fgets(line, sizeof(line), stdin)) {
        size_t len = strlen(line);

        /* 去掉行尾换行符 */
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }

        /* 输入只有一个 "=" 时结束 */
        if (strcmp(line, "=") == 0) break;

        printf("%d\n", EvaluateExpression(line));
    }

    return 0;
}