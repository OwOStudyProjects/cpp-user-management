#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"
#include "../include/file_io.h"

// 全局变量定义
User users[MAX_USERS];
int user_count = 0;

// 获取下一个用户ID
int get_next_id() {
    int max_id = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].id > max_id) {
            max_id = users[i].id;
        }
    }
    return max_id + 1;
}

// 添加用户
void add_user() {
    if (user_count >= MAX_USERS) {
        printf("\n[错误] 用户数量已达上限（%d个）！\n", MAX_USERS);
        return;
    }

    User new_user;
    new_user.id = get_next_id();
    new_user.is_active = 1;

    printf("╔═══════════════════════════════════════╗\n");
    printf("║            添加新用户                 ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    // 获取姓名（不能为空）
    get_non_empty_string(new_user.name, MAX_NAME_LEN, "请输入姓名: ");

    // 获取年龄（必须是有效整数）
    printf("请输入年龄 (0-150): ");
    new_user.age = get_valid_age(-1);

    // 获取邮箱（必须符合格式）
    while (1) {
        get_non_empty_string(new_user.email, MAX_EMAIL_LEN, "请输入邮箱: ");

        if (is_valid_email(new_user.email)) {
            break;
        } else {
            printf("[错误] 邮箱格式不正确，请重新输入\n");
            printf("示例: user@example.com\n");
        }
    }

    users[user_count++] = new_user;
    save_users();

    printf("\n");
    printf("┌─────────────────────────────────────┐\n");
    printf("│  √ 用户添加成功！                   │\n");
    printf("│  用户ID: %-3d                        │\n", new_user.id);
    printf("│  姓名: %-20s         │\n", new_user.name);
    printf("└─────────────────────────────────────┘\n");
}

// 显示所有用户
void display_users() {
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                            用户列表                                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n\n");

    if (user_count == 0) {
        printf("  暂无用户数据。\n");
        return;
    }

    printf("┌────┬──────────────────────┬──────┬────────────────────────────────┐\n");
    printf("│ ID │ 姓名                 │ 年龄 │ 邮箱                           │\n");
    printf("├────┼──────────────────────┼──────┼────────────────────────────────┤\n");

    int active_count = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].is_active) {
            printf("│ %-2d │ %-20s │ %-4d │ %-30s │\n",
                   users[i].id, users[i].name, users[i].age, users[i].email);
            active_count++;
        }
    }

    printf("└────┴──────────────────────┴──────┴────────────────────────────────┘\n");
    printf("\n共有 %d 个活跃用户。\n", active_count);
}

// 搜索用户
void search_user() {
    char name[MAX_NAME_LEN];

    printf("╔═══════════════════════════════════════╗\n");
    printf("║            搜索用户                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    get_non_empty_string(name, MAX_NAME_LEN, "请输入要搜索的用户姓名: ");

    printf("\n--- 搜索结果 ---\n\n");
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].is_active && strstr(users[i].name, name) != NULL) {
            printf("┌─────────────────────────────────────┐\n");
            printf("│ ID: %-3d                             │\n", users[i].id);
            printf("│ 姓名: %-20s          │\n", users[i].name);
            printf("│ 年龄: %-3d                           │\n", users[i].age);
            printf("│ 邮箱: %-20s         │\n", users[i].email);
            printf("└─────────────────────────────────────┘\n\n");
            found = 1;
        }
    }

    if (!found) {
        printf("未找到匹配的用户。\n");
    }
}

// 更新用户信息
void update_user() {
    int id;
    char input[100];

    printf("╔═══════════════════════════════════════╗\n");
    printf("║          更新用户信息                 ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    printf("请输入要更新的用户ID: ");

    // 验证ID输入
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("[错误] 输入失败，请重试: ");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (is_empty_string(input)) {
            printf("[错误] ID不能为空，请重新输入: ");
            continue;
        }

        // 检查是否为数字
        int valid = TRUE;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit((unsigned char)input[i])) {
                valid = FALSE;
                break;
            }
        }

        if (!valid) {
            printf("[错误] ID必须是数字，请重新输入: ");
            continue;
        }

        id = atoi(input);
        break;
    }

    // 查找用户
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id && users[i].is_active) {
            printf("\n当前用户信息:\n");
            printf("  姓名: %s\n", users[i].name);
            printf("  年龄: %d\n", users[i].age);
            printf("  邮箱: %s\n\n", users[i].email);

            printf("--- 请输入新信息 (为空时采用旧数据) ---\n");

            // 更新姓名（不能为空）
            get_string_allow_empty(users[i].name, MAX_NAME_LEN, "新姓名: ");
            /* char new_name[MAX_NAME_LEN];
            printf("新姓名: ");
            if (fgets(new_name, MAX_NAME_LEN, stdin) == NULL) {
                printf("未检测到新姓名输入，当前数据保持不变。\n");
            } else {
                // 移除换行符
                new_name[strcspn(new_name, "\n")] = 0;

                // 如果用户输入非空则更新，否则保留旧数据
                if (!is_empty_string(new_name)) {
                    strncpy(users[i].name, new_name, MAX_NAME_LEN - 1);
                    users[i].name[MAX_NAME_LEN - 1] = '\0';
                }
            } */

            // 更新年龄（必须是有效整数）
            printf("新年龄 (0-150): ");
            users[i].age = get_valid_age(users[i].age);

            // 更新邮箱（必须符合格式）
            while (1) {
                char new_email[MAX_EMAIL_LEN];
                strcpy(new_email, users[i].email);
                get_string_allow_empty(new_email, MAX_EMAIL_LEN, "新邮箱: ");

                if (is_valid_email(new_email)) {
                    strcpy(users[i].email, new_email);
                    break;
                } else {
                    printf("[错误] 邮箱格式不正确，请重新输入\n");
                    printf("示例: user@example.com\n");
                }
            }

            save_users();
            printf("\n√ 用户信息更新成功！\n");
            return;
        }
    }

    printf("\n[错误] 未找到ID为 %d 的用户。\n", id);
}

// 删除用户
void delete_user() {
    int id;
    char input[100];

    printf("╔═══════════════════════════════════════╗\n");
    printf("║            删除用户                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    printf("请输入要删除的用户ID: ");

    // 验证ID输入
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("[错误] 输入失败，请重试: ");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (is_empty_string(input)) {
            printf("[错误] ID不能为空，请重新输入: ");
            continue;
        }

        int valid = TRUE;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit((unsigned char)input[i])) {
                valid = FALSE;
                break;
            }
        }

        if (!valid) {
            printf("[错误] ID必须是数字，请重新输入: ");
            continue;
        }

        id = atoi(input);
        break;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id && users[i].is_active) {
            char confirm;
            printf("\n确认要删除用户 \"%s\" (ID: %d) 吗？(y/n): ", users[i].name, id);
            scanf("%c", &confirm);
            getchar();

            if (confirm == 'y' || confirm == 'Y') {
                users[i].is_active = 0;
                save_users();
                printf("\n√ 用户 \"%s\" (ID: %d) 已删除。\n", users[i].name, id);
            } else {
                printf("\n已取消删除操作。\n");
            }
            return;
        }
    }

    printf("\n[错误] 未找到ID为 %d 的用户。\n", id);
}
