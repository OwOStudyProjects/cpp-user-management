#ifndef USER_H
#define USER_H

#include "common.h"

#define MAX_USERS 100
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char email[MAX_EMAIL_LEN];
    int is_active;
} User;

// 全局变量声明
extern User users[MAX_USERS];
extern int user_count;

// 用户操作函数
void add_user(void);
void display_users(void);
void search_user(void);
void update_user(void);
void delete_user(void);
int get_next_id(void);

#endif
