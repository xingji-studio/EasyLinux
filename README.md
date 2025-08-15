# EasyLinux

## 介绍: 旨在帮助 Linux 新手, Windows 用户, ~~甚至是计算机小白~~舒适的学习 / 使用 Linux 系统.

### 使用对象:
- 对于赛博文盲 ...To tell the truth, 能把 Windows 用好已经很好了.
- 对于Windows 用户, 解释其不同, 劝导其适应 Linux 的操作逻辑^(1).

### (1)回答一些疑问，比如:
- 为什么要输命令?
- 为什么更改一些设置要修改配置文件而不是按下某个设置按钮?
- 为什么用 ls 而不是 dir?
- 为什么软件在 `/bin`或`/opt`而不是在 `Program Files`或`system32`
- 为什么是 `ext4` 而不是 `fat`/`ntfs`?
- 为什么硬盘/U盘要手动挂载?

## 技术细节:
- 使用 C++, Qt6，制作启动器和小程序
- 引导教程使用 Godot 做成游戏风格

## 项目方向:
- 交互式学习平台（游戏化+实用指南结合）
- 核心形式：类似"虚拟实验室"的沙盒环境
- 优势：
  - 避免纯游戏脱离实际，也避免枯燥文档
  - 用户可在安全环境中实操（如模拟终端/文件操作）
  - 即时反馈机制降低挫败感

## 开发者须知

---

#### **一、基础规范**
1. **禁止在业务逻辑中使用 `goto` 语句**
  - 使用结构化控制流 (`if/else`, `for`, `while`, `switch`) 替代

2. **禁止万能头文件（包括自己写的）**
   ```cpp
   // ❌ 禁止
   #include <bits/stdc++.h>
   #include <Windows.h> 

   // ✅ 正确
   #include <vector>
   #include <QString>
   ```

3. **禁止 `using namespace` 污染命名空间**
  - 头文件**严格禁止** `using namespace`
  - 源文件**避免**使用，局部可用 `using std::vector;` 等受限形式
   ```cpp
   // ❌ 错误 (头文件中)
   using namespace Qt;

   // ✅ 允许 (源文件中)
   void foo() {
     using std::vector;
     vector<int> v;
   }
   ```

---

#### **二、Qt 对象生命周期**
4. **有 Parent 的类禁止手动释放**
   ```cpp
   // ❌ 错误
   auto *button = new QPushButton(parent);
   delete button; // 触发未定义行为

   // ✅ 正确
   auto *button = new QPushButton(parent); // 由 parent 自动管理
   ```

5. **无 Parent 对象需明确所有权**
  - 使用 `QScopedPointer` 或智能指针管理
   ```cpp
   QScopedPointer<QFile> file(new QFile("data.txt"));
   ```

---

#### **三、头文件管理**
6. **按需引用原则**
  - 头文件**仅包含自身依赖**（前置声明优先）
  - 实现文件包含**直接使用的头文件**
   ```cpp
   // widget.h
   class QLabel; // 前置声明 ✅
   // ❌ 不包含 #include <QLabel>

   // widget.cpp
   #include "widget.h"
   #include <QLabel> // 按需引用 ✅
   ```

7. **头文件保护**  
   统一使用 `#pragma once`
   ```cpp
   #pragma once
   // 禁止 #ifndef/#define 传统宏
   ```

---

#### **四、国际化**
8. **用户可见字符串**
  - 所有 UI 字符串必须用 `tr()` 包裹
  - 动态字符串使用 `QCoreApplication::translate()`
   ```cpp
   button->setText(tr("Submit"));
   ```

---

#### **五、补充规范**
9. **类型转换**
  - 使用 `static_cast`/`dynamic_cast`，**禁用 C 风格转换**
   ```cpp
   double d = 3.14;
   int i = static_cast<int>(d); // ✅
   // ❌ int i = (int)d;
   ```

10. **智能指针**
  - 优先使用 `std::unique_ptr`/`std::shared_ptr`
  - Qt 对象可用 `QPointer` 做弱引用

11. **信号槽连接**
  - 使用 **Qt5 风格类型安全连接**
    ```cpp
    connect(button, &QPushButton::clicked, this, &MyClass::onClick);
    ```

12. **多线程**
  - 跨线程访问使用 `QMetaObject::invokeMethod`
  - 禁止直接跨线程修改 GUI 对象

13. **资源管理**
  - 文件路径使用 `QDir::toNativeSeparators()`
  - 资源文件通过 Qt Resource System (`qrc`) 加载

14. **编译警告**
  - 在 CMake 中开启严格模式：
    ```cmake
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
    ```

---

#### **六、CMake 规范**
```cmake
# 最低要求
cmake_minimum_required(VERSION 3.16...3.26)
project(MyApp LANGUAGES CXX)

# 强制 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动处理 Qt 资源/UI 文件
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

# 禁止隐式包含目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 添加可执行目标
qt_add_executable(MyApp
  main.cpp
  widget.cpp
)
```

---

#### **七、代码示例**
```cpp
// widget.h
#pragma once
#include <QWidget> // 按需引用

class QLabel; // 前置声明

class Widget : public QWidget {
  Q_OBJECT
public:
  explicit Widget(QWidget *parent = nullptr);

private:
  QLabel *m_label; // 不暴露实现细节
};
```

```cpp
// widget.cpp
#include "widget.h"
#include <QLabel> // 实现文件直接引用

Widget::Widget(QWidget *parent) : QWidget(parent) {
  m_label = new QLabel(tr("Hello Qt6"), this); // 自动内存管理
}
```

---

> 通过遵守本规范，可确保代码的 **安全性、可维护性** 及 **国际化支持**。