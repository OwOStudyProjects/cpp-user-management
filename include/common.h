#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 版本信息
#define VERSION "1.0.0"
#define AUTHOR "HanskiJay"

// 公共常量
#define SUCCESS 0
#define ERROR -1
#define TRUE 1
#define FALSE 0

// 清屏宏定义
#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

// 清除输入缓冲区
#define CLEAR_INPUT_BUFFER() while(getchar() != '\n')

// 暂停函数（按任意键继续）
#define PAUSE() do { \
    printf("\n按回车键继续..."); \
    getchar(); \
} while(0)

// 验证函数声明
int is_valid_email(const char *email);
int is_empty_string(const char *str);
int get_valid_age(int default_age);
void get_non_empty_string(char *buffer, int max_len, const char *prompt);
void get_string_allow_empty(char *buffer, int max_len, const char *prompt);

#endif
