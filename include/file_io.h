#ifndef FILE_IO_H
#define FILE_IO_H

#include "common.h"

#define DATA_DIR "data/"
#define FILENAME DATA_DIR"users.dat"

// 文件操作函数
int load_users(void);
int save_users(void);
int create_data_directory(void);

#endif
