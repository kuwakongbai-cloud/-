/**
 * @file sort.c
 * @brief 排序模块入口（委托转发）
 *
 * 本文件仅作为排序功能的转发层，
 * 实际排序实现在 serchsort.c 的 Sort() 函数中。
 * 这里通过 extern 声明引用该函数。
 */

#include <stdio.h>
#include "Data.h"

/* 
 * 外部函数声明 —— 指向 serchsort.c 中的 Sort() 实现
 */
extern void Sort(Data_Structure *data, int count, const char *method);
