# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -g -O2 `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`

# 定义目标可执行文件和源文件
TARGET = main
SRC = main.c
OBJ = $(SRC:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# 编译规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(TARGET) $(OBJ)

# 运行程序
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install run
