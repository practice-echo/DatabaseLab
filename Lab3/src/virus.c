#include "virus.h"
#include "kmp.h"

#include <stdlib.h>
#include <string.h>

/* 检查 person 是否覆盖 virus 中出现的所有字符
 * 若病毒有某字符在人 DNA 里根本不出现, 则不可能匹配, 可提前 NO
 */
static int chars_covered(const char *virus, int vlen,
                         const char *person, int plen)
{
    unsigned char seen[256] = {0};
    for (int i = 0; i < plen; ++i)
        seen[(unsigned char)person[i]] = 1;
    for (int i = 0; i < vlen; ++i)
        if (!seen[(unsigned char)virus[i]]) return 0;
    return 1;
}

VirusResult virus_detect(const char *virus, int vlen,
                         const char *person, int plen)
{
    if (virus == NULL || person == NULL || vlen <= 0 || plen < 0)
        return VIRUS_ERR;

    /* 人 DNA 比病毒还短, 不可能包含长度为 m 的子串 */
    if (plen < vlen) return VIRUS_NO;

    /* 字符集快速排除 */
    if (!chars_covered(virus, vlen, person, plen))
        return VIRUS_NO;

    const int m = vlen;

    /* 构造 V2 = virus + virus, 长度 2m */
    char *v2   = (char *)malloc((size_t)(2 * m) + 1);
    char *pat  = (char *)malloc((size_t)m + 1);
    int  *next = (int  *)malloc((size_t)m * sizeof(int));
    if (v2 == NULL || pat == NULL || next == NULL) {
        free(v2); free(pat); free(next);
        return VIRUS_ERR;
    }
    memcpy(v2,     virus, (size_t)m);
    memcpy(v2 + m, virus, (size_t)m);
    v2[2 * m] = '\0';
    pat[m]    = '\0';

    VirusResult ret = VIRUS_NO;
    for (int i = 0; i < m; ++i) {
        /* 第 i 个循环移位（V2[i .. i+m-1]） */
        memcpy(pat, v2 + i, (size_t)m);

        if (kmp_build_next(pat, m, next) != 0) {
            ret = VIRUS_ERR;
            break;
        }
        if (kmp_find_with_next(person, plen, pat, m, next) >= 0) {
            ret = VIRUS_YES;
            break;
        }
    }

    free(v2); free(pat); free(next);
    return ret;
}

VirusResult virus_detect_str(const char *virus, const char *person)
{
    if (virus == NULL || person == NULL) return VIRUS_ERR;
    return virus_detect(virus, (int)strlen(virus),
                        person, (int)strlen(person));
}

int virus_detect_stream(FILE *in, FILE *out)
{
    if (in == NULL || out == NULL) return -1;

    /* 4096 字节上限, 足以覆盖本实验所有数据；
     * 若需要支持任意长度, 可改用 getline() 动态分配
     */
    char virus[4096];
    char person[4096];
    int  groups = 0;

    while (fscanf(in, "%4095s %4095s", virus, person) == 2) {
        /* 结束标志：两个都是 "0" */
        if (strcmp(virus, "0") == 0 && strcmp(person, "0") == 0)
            break;

        VirusResult r = virus_detect_str(virus, person);
        if (r == VIRUS_ERR) return -1;

        fprintf(out, "%s\n", r == VIRUS_YES ? "YES" : "NO");
        ++groups;
    }
    return groups;
}

int virus_detect_file(const char *in_path, const char *out_path)
{
    if (in_path == NULL || out_path == NULL) return -1;

    FILE *fin = fopen(in_path, "r");
    if (fin == NULL) return -1;

    FILE *fout = fopen(out_path, "w");
    if (fout == NULL) { fclose(fin); return -1; }

    int r = virus_detect_stream(fin, fout);
    fclose(fin);
    fclose(fout);
    return r;
}