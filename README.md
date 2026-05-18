# 用户管理系统

一个简单的基于C语言的用户管理系统，支持用户的增删改查操作。

## 功能特性

- ✅ 添加用户
- ✅ 显示所有用户
- ✅ 搜索用户（模糊匹配）
- ✅ 更新用户信息
- ✅ 删除用户（逻辑删除）
- ✅ 数据持久化存储

## 编译和运行

### 前置要求

- GCC编译器
- Make工具

### 编译

```bash
make
```

### 运行

```bash
make run
# 或者
./build/bin/user_management
```

### 清理

```bash
make clean       # 清理编译文件
make clean-all   # 清理所有生成文件
```

### 项目结构

```tree
user_management_system/
├── include/          # 头文件
├── src/              # 源代码
├── build/            # 编译输出
├── data/             # 数据文件
└── docs/             # 文档
```
