#include "../include/common.h"

// 检查字符串是否为空或只包含空白字符
int is_empty_string(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return TRUE;
    }

    // 检查是否只包含空白字符
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

// 验证邮箱格式
int is_valid_email(const char *email) {
    if (email == NULL || is_empty_string(email)) {
        return FALSE;
    }

    int at_count = 0;
    int at_pos = -1;
    int dot_after_at = 0;
    int len = strlen(email);

    // 基本长度检查
    if (len < 5) {  // 最短的邮箱如 a@b.c
        return FALSE;
    }

    // 不能以特殊字符开头或结尾
    if (email[0] == '@' || email[0] == '.' ||
        email[len-1] == '@' || email[len-1] == '.') {
        return FALSE;
    }

    // 遍历检查
    for (int i = 0; i < len; i++) {
        char c = email[i];

        if (c == '@') {
            at_count++;
            at_pos = i;
            if (at_count > 1) {
                return FALSE;  // 只能有一个@
            }
            if (i == 0 || i == len - 1) {
                return FALSE;  // @不能在开头或结尾
            }
        } else if (c == '.') {
            if (at_pos != -1 && i > at_pos) {
                dot_after_at = 1;
            }
            // 点不能连续出现
            if (i > 0 && email[i-1] == '.') {
                return FALSE;
            }
        } else if (!isalnum((unsigned char)c) && c != '_' && c != '-' && c != '.') {
            return FALSE;  // 包含非法字符
        }
    }

    // 必须有一个@符号，且@后面必须有点
    return (at_count == 1 && dot_after_at);
}

// 获取有效的年龄输入
int get_valid_age(int default_age) {
    int age;
    char input[100];

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL && default_age == -1) {
            printf("[错误] 输入失败，请重试: ");
            continue;
        }

        // 移除换行符
        input[strcspn(input, "\n")] = 0;

        // 检查是否为空
        if (is_empty_string(input)) {
            if (default_age == -1) {
                printf("[错误] 年龄不能为空，请重新输入: ");
                continue;
            }
            printf("检测到输入为空，已返回默认值。\n");
            return default_age;
        }

        // 检查是否全为数字
        int valid = TRUE;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit((unsigned char)input[i])) {
                valid = FALSE;
                break;
            }
        }

        if (!valid) {
            printf("[错误] 年龄必须是数字，请重新输入: ");
            continue;
        }

        // 转换为整数
        age = atoi(input);

        // 验证范围
        if (age < 0 || age > 150) {
            printf("[错误] 年龄必须在 0-150 之间，请重新输入: ");
            continue;
        }

        return age;
    }
}

// 获取非空字符串
void get_non_empty_string(char *buffer, int max_len, const char *prompt) {
    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, max_len, stdin) == NULL) {
            printf("[错误] 输入失败，请重试\n");
            continue;
        }

        // 移除换行符
        buffer[strcspn(buffer, "\n")] = 0;

        // 检查是否为空
        if (is_empty_string(buffer)) {
            printf("[错误] 输入不能为空，请重新输入\n");
            continue;
        }

        break;
    }
}

// 获取非空字符串 (允许空输入, 不改变buffer)
void get_string_allow_empty(char *buffer, int max_len, const char *prompt) {
    char backup[128]; // 临时备份区
    strncpy(backup, buffer, sizeof(backup));
    backup[sizeof(backup)-1] = '\0'; // 防止溢出

    printf("%s", prompt);

    if (fgets(buffer, max_len, stdin) == NULL) {
        printf("[错误] 输入失败，请重试\n");
        return;
    }

    // 移除换行符
    buffer[strcspn(buffer, "\n")] = 0;

    // 如果输入为空，则恢复原来的值
    if (is_empty_string(buffer)) {
        strncpy(buffer, backup, max_len);
        buffer[max_len - 1] = '\0';
        printf("检测到输入为空，已恢复默认值。\n");
    }
}

