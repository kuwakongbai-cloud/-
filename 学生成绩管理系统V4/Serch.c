/**
 * @file Serch.c
 * @brief 查询入口包装模块
 *
 * 提供 Serch() 和 LookupEntry() 两个包装函数，
 * 分别封装 serchsort.c 中的 Search() 和 Lookup()。
 * 当前 Serch() 函数体为空，为预留接口。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

/**
 * @brief 查询入口（预留接口）
 * @param method 查询方式名称（暂未启用）
 * @param key    查询关键字（暂未启用）
 *
 * 当前为预留函数，函数体为空。
 * 外部 Search() 的调用在 main.c 中直接完成。
 */
void Serch(const char *method, const char *key) {
    /* 这里直接调用 serchsort.c 中的 Search() 函数 */
    extern int *Search(Data_Structure *data, int count, const char *method, const char *key, int *result_count);

}

/**
 * @brief 查找排名入口（包装函数）
 * @param data   学生数据数组
 * @param count  记录总数
 * @param method 查询方式 ("name" / "id")
 * @param key    匹配关键字
 *
 * 对 serchsort.c 中 Lookup() 的简单包装，
 * 通过 extern 声明引入实际实现。
 */
void LookupEntry(Data_Structure *data, int count, const char *method, const char *key) {
    extern void Lookup(Data_Structure *data, int count, const char *method, const char *key);
    Lookup(data, count, method, key);
}
