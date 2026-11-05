/*
 * virus.h - 基于 KMP 的病毒感染检测（病毒DNA为环状）
 *
 * 设计说明:
 *   病毒感染判定 = 病毒的某个长度为 m 的循环移位
 *                  是否作为子串出现在人 DNA 序列中。
 *
 *   内部实现: 把病毒 DNA 复制成 V2 = V + V (长度 2m)，
 *   枚举 V2 中所有长度为 m 的窗口（共 m 个）作为模式串，
 *   依次用人 DNA 调用 KMP 查找。
 */
#ifndef VIRUS_H
#define VIRUS_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 检测结果 */
typedef enum {
    VIRUS_ERR = -1,   /* 参数非法 / 内存不足 */
    VIRUS_NO  =  0,   /* 未感染 */
    VIRUS_YES =  1    /* 感染 */
} VirusResult;

/*
 * 核心检测函数
 *   virus, vlen : 病毒 DNA 及长度（vlen > 0）
 *   person,plen : 人 DNA 及长度
 * 返回: VIRUS_YES / VIRUS_NO / VIRUS_ERR
 */
VirusResult virus_detect(const char *virus, int vlen,
                         const char *person, int plen);

/* C 字符串便捷版（内部自动 strlen） */
VirusResult virus_detect_str(const char *virus, const char *person);

/*
 * 从输入流批量检测, 结果写到输出流
 * 输入格式: 每行 "A B"（A=病毒 DNA, B=人 DNA）；读到 "0 0" 结束
 * 输出格式: 每组一行 "YES" / "NO"
 * 返回: 成功处理的数据组数; 出错返回 -1
 */
int virus_detect_stream(FILE *in, FILE *out);

/*
 * 从输入文件读、结果写到输出文件
 * 返回同上
 */
int virus_detect_file(const char *in_path, const char *out_path);

#ifdef __cplusplus
}
#endif
#endif