/**
 * @file Data.h
 * @brief 学生成绩管理系统 V4 — 数据结构与函数声明
 *
 * 定义了学生记录的结构体 Data_Structure，以及所有对外提供的函数接口。
 * 每条记录代表「一个学生在某门课程上的成绩」。
 */

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Data_Structure
 * @brief 学生成绩记录结构体
 *
 * 每个实例存储一名学生在某一门课程上的成绩信息。
 * 一个学生如果有 n 门课，就会对应 n 条记录。
 */
typedef struct {
    char name[30];        /**< 学生姓名                          */
    int score;            /**< 该门课程的考试成绩（整数分）       */
    char project[6];      /**< 科目名称（如 "数学"、"英语"）     */
    char student_id[30];  /**< 学号                              */
    int student_number;   /**< 序号（预留字段）                  */
    char method[20];      /**< 查询/排序方法标识（"name"/"id"/"score"/"project"） */
} Data_Structure;

/**
 * @brief 录入学生数据
 * @param data  数据数组起始位置
 * @param count 要录入的记录条数
 */
void Input_Data(Data_Structure *data, int count);

/**
 * @brief 通用查询函数
 * @param data         数据数组
 * @param count        记录总数
 * @param method       查询字段类型 ("name"/"id"/"score"/"project")
 * @param key          查询关键字（匹配值）
 * @param result_count 输出参数，匹配到的记录数
 * @return 动态分配的索引数组（调用者负责 free），无匹配返回 NULL
 */
int *Search(Data_Structure *data, int count, const char *method, const char *key, int *result_count);

/**
 * @brief 排序分发函数
 * @param data   数据数组
 * @param count  记录总数
 * @param method 排序方式 ("low-high"/"high-low"/"id_small-big"/"dictionary")
 */
void Sort(Data_Structure *data, int count, const char *method);

/**
 * @brief 查找学生的排名与各科成绩
 * @param data   学生数据数组
 * @param count  记录总数
 * @param method 查询类型 ("name" 按姓名 / "id" 按学号)
 * @param key    匹配关键字（姓名或学号）
 *
 * 功能：先按学生去重汇总各科成绩，再按总分排序计算排名，输出目标学生的各科明细。
 */
void Lookup(Data_Structure *data, int count, const char *method, const char *key);

/**
 * @brief 课程成绩统计分析
 * @param data  数据数组
 * @param count 记录总数
 *
 * 按课程分组，计算每门课程的：
 *   - 总分、平均分
 *   - 优秀(90-100)、良好(80-89)、中等(70-79)、及格(60-69)、不及格(0-59)
 *     各等级人数及百分比
 */
void CourseStatistics(Data_Structure *data, int count);

/**
 * @brief 学生总分与平均分统计
 * @param data  数据数组
 * @param count 记录总数
 *
 * 按学号分组，计算每个学生的总分和平均分，并按总分降序排名输出。
 */
void StudentStatistics(Data_Structure *data, int count);

#endif
