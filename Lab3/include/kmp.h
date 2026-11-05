/*
 * kmp.h - KMP 字符串匹配算法
 */
#ifndef KMP_H
#define KMP_H

#ifdef __cplusplus
extern "C" {
#endif

int kmp_build_next(const char *pat, int m, int *next);

int kmp_find_with_next(const char *text, int n,
                       const char *pat,  int m,
                       const int  *next);

int kmp_find_all_with_next(const char *text, int n,
                           const char *pat,  int m,
                           const int  *next,
                           int *pos, int max);

int kmp_find(const char *text, int n, const char *pat, int m);

int kmp_find_all(const char *text, int n, const char *pat, int m,
                 int *pos, int max);

int kmp_search_str(const char *text, const char *pat);

int kmp_search_all_str(const char *text, const char *pat,
                       int *pos, int max);

#ifdef __cplusplus
}
#endif
#endif