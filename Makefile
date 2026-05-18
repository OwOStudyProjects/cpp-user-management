# 编译器设置
CC = g++
LDFLAGS =

# 检测操作系统并设置相应的编译选项
ifeq ($(OS),Windows_NT)
    # Windows系统 - 使用GBK编码匹配控制台
    CFLAGS = -Wall -Wextra -g -I./include -finput-charset=UTF-8 -fexec-charset=GBK
    MKDIR = if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
    RM = rmdir /s /q
    TARGET_EXT = .exe
else
    # Unix/Linux/Mac系统 - 使用UTF-8
    CFLAGS = -Wall -Wextra -g -I./include
    MKDIR = mkdir -p $(1)
    RM = rm -rf
    TARGET_EXT =
endif

# 目录设置
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# 目标文件
TARGET = $(BIN_DIR)/user_management$(TARGET_EXT)
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# 默认目标
all: directories $(TARGET)

# 创建必要的目录
directories:
	$(call MKDIR,$(OBJ_DIR))
	$(call MKDIR,$(BIN_DIR))
	$(call MKDIR,data)

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo 编译成功! 可执行文件: $(TARGET)

# 编译源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 运行程序
run: all
	@$(TARGET)

# 清理编译文件
clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(subst /,\,$(BUILD_DIR))" $(RM) "$(subst /,\,$(BUILD_DIR))"
	@echo 清理完成
else
	$(RM) $(BUILD_DIR)
	@echo 清理完成
endif

# 清理所有生成文件（包括数据）
clean-all: clean
ifeq ($(OS),Windows_NT)
	@if exist "data" $(RM) "data"
	@echo 清理完成（包括数据文件）
else
	$(RM) data
	@echo 清理完成（包括数据文件）
endif

# 显示帮助
help:
	@echo 可用的make目标:
	@echo   mingw32-make          - 编译项目
	@echo   mingw32-make run      - 编译并运行
	@echo   mingw32-make clean    - 清理编译文件
	@echo   mingw32-make clean-all- 清理所有生成文件
	@echo   mingw32-make help     - 显示此帮助信息

.PHONY: all directories clean clean-all run help
