#include "../include/menu.h"
#include "../include/user.h"
#include "../include/file_io.h"

// 显示菜单头部
void print_header() {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        用户管理系统 v%s            ║\n", VERSION);
    printf("╚═══════════════════════════════════════╝\n");
}

// 显示菜单
void show_menu() {
    int choice;

    while (1) {
        CLEAR_SCREEN();  // 清屏
        print_header();

        printf("\n========== 主菜单 ==========\n");
        printf("1. 添加用户\n");
        printf("2. 显示所有用户\n");
        printf("3. 搜索用户\n");
        printf("4. 更新用户信息\n");
        printf("5. 删除用户\n");
        printf("6. 退出系统\n");
        printf("============================\n");
        printf("请选择操作 (1-6): ");

        if (scanf("%d", &choice) != 1) {
            CLEAR_INPUT_BUFFER();
            CLEAR_SCREEN();
            printf("\n[错误] 输入无效，请输入数字！\n");
            PAUSE();
            continue;
        }
        getchar(); // 清除输入缓冲区的换行符

        CLEAR_SCREEN();  // 执行操作前清屏

        switch (choice) {
            case 1:
                add_user();
                PAUSE();
                break;
            case 2:
                display_users();
                PAUSE();
                break;
            case 3:
                search_user();
                PAUSE();
                break;
            case 4:
                update_user();
                PAUSE();
                break;
            case 5:
                delete_user();
                PAUSE();
                break;
            case 6:
                save_users();
                CLEAR_SCREEN();
                printf("\n感谢使用！再见！\n\n");
                exit(0);
            default:
                printf("\n[错误] 无效选择，请输入1-6之间的数字！\n");
                PAUSE();
        }
    }
}
