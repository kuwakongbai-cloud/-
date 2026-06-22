/**
 * @file main.c
 * @brief 学生成绩管理系统 V4 — 主程序入口
 *
 * 提供菜单循环，根据用户选择调用对应的功能模块：
 *   1 - 录入数据（Data.c）
 *   2 - 查询记录（serchsort.c Search）
 *   3 - 排序数据（serchsort.c Sort）
 *   4 - 查找学生排名与各科成绩（serchsort.c Lookup）
 *   5 - 课程成绩统计（serchsort.c CourseStatistics）
 *   6 - 学生总分与平均分统计（serchsort.c StudentStatistics）
 *   7 - 显示全部数据
 *   0 - 退出系统
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

#define MAX_RECORDS 500  /**< 系统能容纳的最大记录条数 */

/**
 * @brief 主函数
 * @return 0 正常退出
 *
 * 初始化数据数组后进入 while(1) 循环：
 *   - 打印主菜单
 *   - 等待用户输入选项
 *   - 根据选项调用对应功能或退出
 *   - 录入数据时检查 count 是否超限
 *   - 各功能执行前检查数据是否为空
 */
int main(void) {
    Data_Structure data[MAX_RECORDS];
    int count = 0;
    int choice;

    printf("╔══════════════════════════════════════╗\n");
    printf("║     学 生 成 绩 管 理 系 统 V4      ║\n");
    printf("╚══════════════════════════════════════╝\n");

    while (1) {
        printf("\n");
        printf("┌──────────────────────────────────────┐\n");
        printf("│  1. 录入学生数据                     │\n");
        printf("│  2. 查询学生                         │\n");
        printf("│  3. 排序数据                         │\n");
        printf("│  4. 查找学生排名与各科成绩           │\n");
        printf("│  5. 课程成绩统计                     │\n");
        printf("│  6. 学生总分与平均分统计             │\n");
        printf("│  7. 显示全部数据                     │\n");
        printf("│  0. 退出系统                         │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        getchar(); /* 吃掉换行符 */

        switch (choice) {
            case 0:
                printf("感谢使用，再见！\n");
                return 0;

            case 1: {
                /* ── 录入学生数据 ── */
                printf("请输入要录入的学生记录条数: ");
                int n;
                scanf("%d", &n);
                getchar();

                if (n <= 0 || count + n > MAX_RECORDS) {
                    printf("数量不合法或超过最大容量 %d！\n", MAX_RECORDS);
                    break;
                }
                Input_Data(&data[count], n);
                count += n;
                printf("录入完成，当前共有 %d 条记录。\n", count);
                break;
            }

            case 2: {
                /* ── 查询学生 ── */
                if (count == 0) {
                    printf("暂无数据，请先录入！\n");
                    break;
                }
                printf("查询方式 (name / id / score / project): ");
                char method[20], key[50];
                scanf("%s", method);
                printf("查询关键字: ");
                scanf("%s", key);

                int result_count = 0;
                int *results = Search(data, count, method, key, &result_count);

                if (results == NULL || result_count == 0) {
                    printf("未找到匹配的记录。\n");
                } else {
                    printf("\n找到 %d 条记录:\n", result_count);
                    printf("%-6s %-12s %-6s %-12s %-6s\n",
                           "序号", "姓名", "科目", "学号", "成绩");
                    for (int i = 0; i < result_count; i++) {
                        int idx = results[i];
                        printf("%-6d %-12s %-6s %-12s %-6d\n",
                               idx + 1,
                               data[idx].name,
                               data[idx].project,
                               data[idx].student_id,
                               data[idx].score);
                    }
                    free(results);
                }
                break;
            }

            case 3: {
                /* ── 排序数据 ── */
                if (count == 0) {
                    printf("暂无数据，请先录入！\n");
                    break;
                }
                printf("排序方式:\n");
                printf("  low-high      分数从低到高\n");
                printf("  high-low      分数从高到低\n");
                printf("  id_small-big  学号从小到大\n");
                printf("  dictionary    姓名按字典序\n");
                printf("请选择: ");
                char method[20];
                scanf("%s", method);

                Sort(data, count, method);
                printf("排序完成。\n");

                /* 显示排序后的数据 */
                printf("\n排序后数据:\n");
                printf("%-6s %-12s %-6s %-12s %-6s\n",
                       "序号", "姓名", "科目", "学号", "成绩");
                for (int i = 0; i < count; i++) {
                    printf("%-6d %-12s %-6s %-12s %-6d\n",
                           i + 1, data[i].name, data[i].project,
                           data[i].student_id, data[i].score);
                }
                break;
            }

            case 4: {
                /* ── 查找学生排名与各科成绩 ── */
                if (count == 0) {
                    printf("暂无数据，请先录入！\n");
                    break;
                }
                printf("查找方式 (name / id): ");
                char method[20], key[50];
                scanf("%s", method);
                printf("关键字: ");
                scanf("%s", key);

                Lookup(data, count, method, key);
                break;
            }

            case 5: {
                /* ── 课程成绩统计 ── */
                if (count == 0) {
                    printf("暂无数据，请先录入！\n");
                    break;
                }
                CourseStatistics(data, count);
                break;
            }

            case 6: {
                /* ── 学生总分与平均分统计 ── */
                if (count == 0) {
                    printf("暂无数据，请先录入！\n");
                    break;
                }
                StudentStatistics(data, count);
                break;
            }

            case 7: {
                /* ── 显示全部数据 ── */
                if (count == 0) {
                    printf("暂无数据，请先录入！\n");
                    break;
                }
                printf("\n全部数据（共 %d 条）:\n", count);
                printf("%-6s %-12s %-6s %-12s %-6s\n",
                       "序号", "姓名", "科目", "学号", "成绩");
                for (int i = 0; i < count; i++) {
                    printf("%-6d %-12s %-6s %-12s %-6d\n",
                           i + 1, data[i].name, data[i].project,
                           data[i].student_id, data[i].score);
                }
                break;
            }

            default:
                printf("无效选择，请重新输入！\n");
                break;
        }
    }

    return 0;
}
