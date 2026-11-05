#include "kmp.h"
#include <stdlib.h>
#include <string.h>

int kmp_build_next(const char *pat, int m, int *next)
{
    if (pat == NULL || next == NULL || m <= 0) return -1;
    next[0] = 0;
    int len = 0;
    for (int i = 1; i < m; ++i) {
        while (len > 0 && pat[i] != pat[len])
            len = next[len - 1];
        if (pat[i] == pat[len]) ++len;
        next[i] = len;
    }
    return 0;
}

int kmp_find_with_next(const char *text, int n,
                       const char *pat,  int m,
                       const int  *next)
{
    if (pat == NULL || next == NULL) return -1;
    if (m <= 0) return 0;
    if (text == NULL || n < m) return -1;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pat[j]) j = next[j - 1];
        if (text[i] == pat[j]) ++j;
        if (j == m) return i - m + 1;
    }
    return -1;
}

int kmp_find_all_with_next(const char *text, int n,
                           const char *pat,  int m,
                           const int  *next,
                           int *pos, int max)
{
    if (pat == NULL || next == NULL || m <= 0) return 0;
    if (text == NULL || n < m) return 0;
    int j = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pat[j]) j = next[j - 1];
        if (text[i] == pat[j]) ++j;
        if (j == m) {
            if (pos != NULL && cnt < max) pos[cnt] = i - m + 1;
            ++cnt;
            j = next[j - 1];
        }
    }
    return cnt;
}

int kmp_find(const char *text, int n, const char *pat, int m)
{
    if (pat == NULL) return -1;
    if (m <= 0) return 0;
    if (text == NULL || n < m) return -1;
    int *next = (int *)malloc((size_t)m * sizeof(int));
    if (next == NULL) return -1;
    kmp_build_next(pat, m, next);
    int r = kmp_find_with_next(text, n, pat, m, next);
    free(next);
    return r;
}

int kmp_find_all(const char *text, int n, const char *pat, int m,
                 int *pos, int max)
{
    if (pat == NULL || m <= 0) return 0;
    if (text == NULL || n < m) return 0;
    int *next = (int *)malloc((size_t)m * sizeof(int));
    if (next == NULL) return 0;
    kmp_build_next(pat, m, next);
    int cnt = kmp_find_all_with_next(text, n, pat, m, next, pos, max);
    free(next);
    return cnt;
}

int kmp_search_str(const char *text, const char *pat)
{
    if (text == NULL || pat == NULL) return -1;
    return kmp_find(text, (int)strlen(text), pat, (int)strlen(pat));
}

int kmp_search_all_str(const char *text, const char *pat,
                       int *pos, int max)
{
    if (text == NULL || pat == NULL) return 0;
    return kmp_find_all(text, (int)strlen(text),
                        pat,  (int)strlen(pat), pos, max);
}