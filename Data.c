/**
 * @file Data.c
 * @brief 数据录入模块
 *
 * 负责从标准输入读取学生成绩数据并存入 Data_Structure 数组。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

/**
 * @brief 录入学生成绩数据
 * @param data  数据数组的起始位置（调用者指定偏移）
 * @param count 要录入的记录条数
 *
 * 从键盘读取 count 条记录，每条记录包含：
 *   姓名 成绩 科目 学号
 * 四个字段以空格分隔输入。
 *
 * 每条记录的 method 字段初始化为空字符串。
 */
void Input_Data(Data_Structure *data, int count) {
    for (int i = 0; i < count; i++) {
        printf("\n--- 第 %d 个学生 ---\n", i + 1);
        printf("姓名 成绩 科目 学号: ");
        scanf("%s %d %s %s",
              data[i].name,
              &data[i].score,
              data[i].project,
              data[i].student_id);
        /* 清空查询/排序方法字段 */
        data[i].method[0] = '\0';
    }
}
