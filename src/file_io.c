#include "../include/file_io.h"
#include "../include/user.h"

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(dir) mkdir(dir, 0755)
#endif

// 创建数据目录
int create_data_directory(void) {
    MKDIR(DATA_DIR);
    return SUCCESS;
}

// 从文件加载用户数据
int load_users(void) {
    create_data_directory();

    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("未找到数据文件，将创建新文件。\n");
        return SUCCESS;
    }

    fread(&user_count, sizeof(int), 1, file);
    fread(users, sizeof(User), user_count, file);
    fclose(file);
    printf("成功加载 %d 个用户数据。\n", user_count);
    return SUCCESS;
}

// 保存用户数据到文件
int save_users(void) {
    create_data_directory();

    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("无法保存数据！\n");
        return ERROR;
    }

    fwrite(&user_count, sizeof(int), 1, file);
    fwrite(users, sizeof(User), user_count, file);
    fclose(file);
    printf("数据已保存。\n");
    return SUCCESS;
}
