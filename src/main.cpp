#include <QApplication>
#include <QThread>
#include <QPropertyAnimation>

#include "MainWindow.h"
#include "SplashScreen.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建启动画面
    SplashScreen splash;
    splash.show();

    // 强制立即显示
    QApplication::processEvents();

    // 模拟加载过程
    QStringList loadingSteps = {
        "正在加载核心模块...",
        "初始化用户界面...",
        "准备学习资源...",
        "检查系统兼容性...",
        "优化性能设置...",
        "启动交互式教程..."
    };

    for (int i = 0; i <= 100; i += 5) {
        const int stepIndex = qMin(i / 20, loadingSteps.size() - 1);
        splash.updateProgress(i, loadingSteps[stepIndex]);
        QThread::msleep(50); // 睡50毫秒
        QApplication::processEvents();
    }

    MainWindow mainWindow;

    // 淡入动画
    auto *fadeIn = new QPropertyAnimation(&mainWindow, "windowOpacity");
    fadeIn->setDuration(800);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::OutCubic);

    // 显示主窗口并启动动画
    mainWindow.show();
    fadeIn->start();

    // 关闭启动画面
    splash.close();
    const int ret = QApplication::exec();
    delete fadeIn;

    return ret;
}