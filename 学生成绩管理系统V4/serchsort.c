/**
 * @file serchsort.c
 * @brief 核心功能模块：查询、排序、排名查找、课程统计、学生统计
 *
 * 本文件包含系统的大多数核心逻辑函数：
 *   - Search()          通用查询（按姓名/学号/成绩/科目）
 *   - Sort()            排序分发（冒泡排序 × 4 种策略）
 *   - Lookup()          查找学生排名与各科成绩
 *   - CourseStatistics() 课程成绩分段统计
 *   - StudentStatistics() 学生总分与平均分排名
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

/**
 * @brief 通用查询函数
 * @param data         学生数据数组
 * @param count        记录总数
 * @param method       查询字段类型
 *                     "name"    —— 按学生姓名匹配
 *                     "id"      —— 按学号匹配
 *                     "score"   —— 按分数匹配
 *                     "project" —— 按科目匹配
 * @param key          查询关键字（要与对应字段的值做比较）
 * @param result_count 输出参数，记录匹配到的记录数量
 * @return int* 动态分配的索引数组，每个元素是 data 数组中匹配记录的索引
 *
 * 实现原理：
 *   1. 第一遍遍历数组，统计匹配的记录数量
 *   2. 根据匹配数量动态分配结果数组
 *   3. 第二遍遍历，将匹配的索引填入结果数组
 *   两次遍历确保结果数组大小精确，不浪费内存。
 *   调用者必须使用 free() 释放返回值。
 */
int *Search(Data_Structure *data, int count, const char *method, const char *key, int *result_count) {
    if (data == NULL || method == NULL || key == NULL || result_count == NULL) {
        return NULL;
    }

    /* 先遍历一次统计匹配数量 */
    int matched = 0;
    for (int i = 0; i < count; i++) {
        int match = 0;
        if (strcmp(method, "name") == 0) {
            if (strcmp(data[i].name, key) == 0) match = 1;
        } else if (strcmp(method, "id") == 0) {
            if (strcmp(data[i].student_id, key) == 0) match = 1;
        } else if (strcmp(method, "score") == 0) {
            if (data[i].score == atoi(key)) match = 1;
        } else if (strcmp(method, "project") == 0) {
            if (strcmp(data[i].project, key) == 0) match = 1;
        } else {
            printf("未知的查询方法: %s\n", method);
            *result_count = 0;
            return NULL;
        }
        if (match) matched++;
    }

    *result_count = matched;
    if (matched == 0) return NULL;

    /* 分配结果数组并填入匹配索引 */
    int *results = (int *)malloc(sizeof(int) * matched);
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < count; i++) {
        int match = 0;
        if (strcmp(method, "name") == 0) {
            if (strcmp(data[i].name, key) == 0) match = 1;
        } else if (strcmp(method, "id") == 0) {
            if (strcmp(data[i].student_id, key) == 0) match = 1;
        } else if (strcmp(method, "score") == 0) {
            if (data[i].score == atoi(key)) match = 1;
        } else if (strcmp(method, "project") == 0) {
            if (strcmp(data[i].project, key) == 0) match = 1;
        }
        if (match) {
            results[idx++] = i;
        }
    }

    return results;
}

/**
 * @brief 排序分发函数
 * @param data   数据数组（原地排序，会修改原数组顺序）
 * @param count  记录总数
 * @param method 排序方式：
 *   "low-high"      —— 成绩从低到高（升序）
 *   "high-low"      —— 成绩从高到低（降序）
 *   "id_small-big"  —— 学号从小到大（字符串升序）
 *   "dictionary"    —— 姓名按字典序（字符串升序）
 *
 * 实现原理：
 *   所有排序均采用冒泡排序（Bubble Sort）算法。
 *   通过两层嵌套循环，相邻两两比较并交换，
 *   每轮将当前未排序部分的最大（或最小）元素"冒泡"到末尾。
 *   时间复杂度 O(n²)，适合数据量较小的场景。
 */
void Sort(Data_Structure *data, int count, const char *method) {
    if (data == NULL || method == NULL || count <= 0) return;

    if (strcmp(method, "low-high") == 0) {
        /* 分数从低到高（升序冒泡） */
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (data[j].score > data[j + 1].score) {
                    Data_Structure temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
    else if (strcmp(method, "high-low") == 0) {
        /* 分数从高到低（降序冒泡） */
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (data[j].score < data[j + 1].score) {
                    Data_Structure temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
    else if (strcmp(method, "id_small-big") == 0) {
        /* 学号从小到大（字符串比较冒泡） */
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (strcmp(data[j].student_id, data[j + 1].student_id) > 0) {
                    Data_Structure temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
    else if (strcmp(method, "dictionary") == 0) {
        /* 姓名按字典序（字符串比较冒泡） */
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (strcmp(data[j].name, data[j + 1].name) > 0) {
                    Data_Structure temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
    else {
        printf("未知的排序方法: %s\n", method);
    }
}

/**
 * @brief 查找学生排名与各科成绩
 * @param data   学生数据数组（每科一条记录）
 * @param count  记录总数
 * @param method 查询方式 ("name" 按姓名 / "id" 按学号)
 * @param key    匹配关键字
 *
 * 实现原理：
 *   第一步 — 学生去重与成绩汇总
 *     遍历所有记录，按学号去重，收集每个学生的各科名称及成绩。
 *     使用局部数组 ids[]/names[] 存储不重复学生信息，
 *     subjects[][]/scores[][] 存储各科目成绩（最多支持 20 门课）。
 *   第二步 — 查找目标学生
 *     在去重后的列表中，按 method+key 查找目标学生。
 *   第三步 — 输出结果
 *     以表格形式输出该学生的姓名、学号及各科成绩。
 *   注：本函数仅展示成绩明细，排名计算在 StudentStatistics() 中。
 */
void Lookup(Data_Structure *data, int count, const char *method, const char *key) {
    if (data == NULL || method == NULL || key == NULL || count <= 0) {
        printf("参数错误：数据为空或参数无效。\n");
        return;
    }

    /* 只接受 name 和 id 两种查找方式 */
    if (strcmp(method, "name") != 0 && strcmp(method, "id") != 0) {
        printf("不支持的查找方式: %s（请使用 \"name\" 或 \"id\"）\n", method);
        return;
    }

    /* ── 第一步：提取所有不重复的学生（按学号去重），收集各科成绩 ── */
    #define MAX_UNIQUE 500
    char  ids[MAX_UNIQUE][30];          /* 学号列表              */
    char  names[MAX_UNIQUE][30];        /* 姓名列表              */
    int   subj_count[MAX_UNIQUE];       /* 各学生的科目数         */
    char  subjects[MAX_UNIQUE][20][6];  /* 科目名称              */
    int   scores[MAX_UNIQUE][20];       /* 各科成绩              */
    int   unique = 0;                   /* 不重复学生计数         */

    for (int i = 0; i < count; i++) {
        /* 在已收集的列表里查找该学号 */
        int found = -1;
        for (int j = 0; j < unique; j++) {
            if (strcmp(ids[j], data[i].student_id) == 0) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            /* 新学生 */
            if (unique >= MAX_UNIQUE) {
                printf("学生数量超过上限 %d，仅处理前 %d 人。\n", MAX_UNIQUE, MAX_UNIQUE);
                break;
            }
            strcpy(ids[unique], data[i].student_id);
            strcpy(names[unique], data[i].name);
            subj_count[unique] = 1;
            strcpy(subjects[unique][0], data[i].project);
            scores[unique][0] = data[i].score;
            unique++;
        } else {
            /* 已存在，添加新科目成绩 */
            int idx = subj_count[found];
            if (idx < 20) {
                strcpy(subjects[found][idx], data[i].project);
                scores[found][idx] = data[i].score;
                subj_count[found]++;
            }
        }
    }

    if (unique == 0) {
        printf("没有学生数据。\n");
        return;
    }

    /* ── 第二步：查找目标学生 ── */
    int target_idx = -1;
    for (int i = 0; i < unique; i++) {
        int match = 0;
        if (strcmp(method, "name") == 0) {
            if (strcmp(names[i], key) == 0) match = 1;
        } else if (strcmp(method, "id") == 0) {
            if (strcmp(ids[i], key) == 0) match = 1;
        }

        if (match) {
            target_idx = i;
            break;
        }
    }

    if (target_idx == -1) {
        printf("未找到 %s 为「%s」的学生。\n",
               strcmp(method, "name") == 0 ? "姓名" : "学号", key);
        return;
    }

    /* ── 第三步：输出查找结果 ── */
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║         学 生 查 找 结 果            ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  姓名：%-26s ║\n", names[target_idx]);
    printf("║  学号：%-26s ║\n", ids[target_idx]);
    printf("╠══════════════════════════════════════╣\n");
    printf("║          各 科 成 绩                 ║\n");
    printf("╠══════════════════════════════════════╣\n");

    for (int k = 0; k < subj_count[target_idx]; k++) {
        printf("║  %-6s ： %-4d                       ║\n",
               subjects[target_idx][k], scores[target_idx][k]);
    }

    printf("╚══════════════════════════════════════╝\n");
    printf("\n");

    #undef MAX_UNIQUE
}

/**
 * @brief 课程成绩统计分析
 * @param data  数据数组
 * @param count 记录总数
 *
 * 实现原理：
 *   1. 遍历所有记录，提取不重复的课程名称列表（最多 50 门课）
 *   2. 针对每门课程，遍历全数组，统计：
 *      - 学生总数、总分
 *      - 各等级人数（优秀 90-100 / 良好 80-89 / 中等 70-79 / 及格 60-69 / 不及格 0-59）
 *   3. 计算平均分和各等级百分比
 *   4. 以表格式输出统计结果
 */
void CourseStatistics(Data_Structure *data, int count) {
    if (data == NULL || count <= 0) {
        printf("没有数据可供统计。\n");
        return;
    }

    /* ── 第一步：收集所有不重复的课程 ── */
    #define MAX_COURSES 50
    char  courses[MAX_COURSES][6];     /* 课程名称列表              */
    int   course_count = 0;            /* 不重复课程数              */

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j], data[i].project) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (course_count >= MAX_COURSES) {
                printf("课程数量超过上限 %d，仅处理前 %d 门。\n", MAX_COURSES, MAX_COURSES);
                break;
            }
            strcpy(courses[course_count], data[i].project);
            course_count++;
        }
    }

    if (course_count == 0) {
        printf("没有课程数据。\n");
        return;
    }

    /* ── 第二步：逐门课程统计 ── */
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        课 程 成 绩 统 计 分 析                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════╝\n");

    for (int c = 0; c < course_count; c++) {
        int total_students = 0;       /* 该课程学生总数            */
        int sum_score = 0;            /* 总分                      */
        int excellent = 0;            /* 优秀 90-100               */
        int good = 0;                 /* 良好 80-89                */
        int medium = 0;               /* 中等 70-79                */
        int pass = 0;                 /* 及格 60-69                */
        int fail = 0;                 /* 不及格 0-59               */

        /* 遍历所有记录，统计本课程 */
        for (int i = 0; i < count; i++) {
            if (strcmp(data[i].project, courses[c]) != 0) continue;

            total_students++;
            sum_score += data[i].score;

            if (data[i].score >= 90 && data[i].score <= 100) {
                excellent++;
            } else if (data[i].score >= 80 && data[i].score <= 89) {
                good++;
            } else if (data[i].score >= 70 && data[i].score <= 79) {
                medium++;
            } else if (data[i].score >= 60 && data[i].score <= 69) {
                pass++;
            } else {
                fail++;
            }
        }

        if (total_students == 0) continue;

        float average = (float)sum_score / total_students;

        /* 计算百分比 */
        float pct_excellent = (float)excellent / total_students * 100.0f;
        float pct_good      = (float)good      / total_students * 100.0f;
        float pct_medium    = (float)medium    / total_students * 100.0f;
        float pct_pass      = (float)pass      / total_students * 100.0f;
        float pct_fail      = (float)fail      / total_students * 100.0f;

        /* ── 输出 ── */
        printf("\n");
        printf("┌──────────────────────────────────────────────────────────────────────┐\n");
        printf("│  课程：%-6s                                                         │\n", courses[c]);
        printf("├──────────────────────────────────────────────────────────────────────┤\n");
        printf("│  学生人数：%3d      总分：%6d      平均分：%8.2f                │\n",
               total_students, sum_score, average);
        printf("├──────────────────────────────────────────────────────────────────────┤\n");
        printf("│  等级分布                                                            │\n");
        printf("├─────────────┬──────────┬─────────────────────────────────────────────┤\n");
        printf("│    等级     │   人数   │     占比                                    │\n");
        printf("├─────────────┼──────────┼─────────────────────────────────────────────┤\n");
        printf("│  优秀       │    %3d   │  %6.2f%%                                  │\n", excellent, pct_excellent);
        printf("│  (90-100)   │          │                                             │\n");
        printf("│  良好       │    %3d   │  %6.2f%%                                  │\n", good, pct_good);
        printf("│  (80-89)    │          │                                             │\n");
        printf("│  中等       │    %3d   │  %6.2f%%                                  │\n", medium, pct_medium);
        printf("│  (70-79)    │          │                                             │\n");
        printf("│  及格       │    %3d   │  %6.2f%%                                  │\n", pass, pct_pass);
        printf("│  (60-69)    │          │                                             │\n");
        printf("│  不及格     │    %3d   │  %6.2f%%                                  │\n", fail, pct_fail);
        printf("│  (0-59)     │          │                                             │\n");
        printf("└─────────────┴──────────┴─────────────────────────────────────────────┘\n");
    }

    #undef MAX_COURSES
}

/**
 * @brief 学生总分与平均分统计
 * @param data  数据数组
 * @param count 记录总数
 *
 * 实现原理：
 *   1. 遍历所有记录，按学号去重，同时累加每个学生的总分和科目数
 *   2. 使用冒泡排序按总分从高到低对学生进行排名
 *   3. 以表格式输出排名、学号、姓名、总分、平均分
 */
void StudentStatistics(Data_Structure *data, int count) {
    if (data == NULL || count <= 0) {
        printf("没有数据可供统计。\n");
        return;
    }

    /* ── 第一步：收集所有不重复的学生 ── */
    #define MAX_STUDENTS 500
    char  ids[MAX_STUDENTS][30];          /* 学号列表                  */
    char  names[MAX_STUDENTS][30];        /* 姓名列表                  */
    int   course_cnt[MAX_STUDENTS];       /* 各学生选课数              */
    int   total_score[MAX_STUDENTS];      /* 各学生总分                */
    int   unique = 0;                     /* 不重复学生计数            */

    for (int i = 0; i < count; i++) {
        int found = -1;
        for (int j = 0; j < unique; j++) {
            if (strcmp(ids[j], data[i].student_id) == 0) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            /* 新学生 */
            if (unique >= MAX_STUDENTS) {
                printf("学生数量超过上限 %d，仅处理前 %d 人。\n", MAX_STUDENTS, MAX_STUDENTS);
                break;
            }
            strcpy(ids[unique], data[i].student_id);
            strcpy(names[unique], data[i].name);
            course_cnt[unique] = 1;
            total_score[unique] = data[i].score;
            unique++;
        } else {
            /* 已有学生，累加 */
            course_cnt[found]++;
            total_score[found] += data[i].score;
        }
    }

    if (unique == 0) {
        printf("没有学生数据。\n");
        return;
    }

    /* ── 第二步：按总分从高到低排序（冒泡排序） ── */
    for (int i = 0; i < unique - 1; i++) {
        for (int j = 0; j < unique - 1 - i; j++) {
            if (total_score[j] < total_score[j + 1]) {
                /* 交换总分 */
                int temp_score = total_score[j];
                total_score[j] = total_score[j + 1];
                total_score[j + 1] = temp_score;

                /* 交换选课数 */
                int temp_cnt = course_cnt[j];
                course_cnt[j] = course_cnt[j + 1];
                course_cnt[j + 1] = temp_cnt;

                /* 交换学号 */
                char temp_id[30];
                strcpy(temp_id, ids[j]);
                strcpy(ids[j], ids[j + 1]);
                strcpy(ids[j + 1], temp_id);

                /* 交换姓名 */
                char temp_name[30];
                strcpy(temp_name, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp_name);
            }
        }
    }

    /* ── 第三步：输出统计结果 ── */
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     学 生 总 分 与 平 均 分 统 计                        ║\n");
    printf("╠══════╦══════════════════════╦══════════════════════╦════════╦════════════╣\n");
    printf("║ 排名 ║       学号           ║        姓名          ║  总分  ║   平均分   ║\n");
    printf("╠══════╬══════════════════════╬══════════════════════╬════════╬════════════╣\n");

    for (int i = 0; i < unique; i++) {
        float avg = (float)total_score[i] / course_cnt[i];
        printf("║ %3d  ║  %-18s ║  %-16s ║  %5d  ║  %8.2f  ║\n",
               i + 1, ids[i], names[i], total_score[i], avg);
    }

    printf("╚══════╩══════════════════════╩══════════════════════╩════════╩════════════╝\n");
    printf("\n");

    #undef MAX_STUDENTS
}
