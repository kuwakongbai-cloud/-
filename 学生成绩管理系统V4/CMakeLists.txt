cmake_minimum_required(VERSION 3.10)
project(学生成绩管理系统V4 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(student_ms
    main.c
    Data.c
    Serch.c
    serchsort.c
    sort.c
    persent.c
)
