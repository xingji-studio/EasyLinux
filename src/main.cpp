/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyleft (ɔ) 2025 POINT org., XINGJI Studio.
 *
 * 此程序是自由软件：您可以根据自由软件基金会发布的 GNU 通用公共许可证条款重新分发和/或修改它，
 * 许可证版本 3（GPLv3）或任何更高版本（由您选择）。
 *
 * 分发此程序是希望它有用，但**没有任何担保**；甚至没有适销性或特定用途适用性的默示担保。
 * 有关详细信息，请参阅 GNU 通用公共许可证。
 *
 * 您应已随此程序收到 GNU GPLv3 的副本。如果没有，请访问 <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QThread>
#include <QPropertyAnimation>
#include <filesystem>
#include <QDebug>

#include "MainWindow.h"
#include "SplashScreen.h"

#define VERSION "Easy Linux alpha 1.2"

int main(int argc, char *argv[]) {
    qDebug() << VERSION;

    QApplication app(argc, argv);
    // 创建启动画面
    SplashScreen splash(nullptr, VERSION);
    splash.show();
    // 强制立即显示
    QApplication::processEvents();

    // 加载过程
    QStringList loadingSteps = {
        "正在加载核心模块...",
        "初始化用户界面...",
        "准备学习资源...",
        "检查系统环境...",
        "启动交互式教程..."
    };

//    for (int i = 0; i <= 100; i += 5) {
//        const int stepIndex = qMin<int, int>(i / 20, int(loadingSteps.size() - 1));
//        splash.updateProgress(i, loadingSteps[stepIndex]);
//        QThread::msleep(50); // 睡50毫秒, 当加载了
//        QApplication::processEvents();
//    }

    splash.updateProgress(0, loadingSteps[0]);
    auto *mainWindow = new MainWindow();
    splash.updateProgress(25, loadingSteps[1]);
    // 淡入动画
    auto *fadeIn = new QPropertyAnimation(mainWindow, "windowOpacity");
    fadeIn->setDuration(300);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::OutCubic);

    splash.updateProgress(100, loadingSteps[4]);

    // 显示主窗口并启动动画
    mainWindow->show();
    fadeIn->start();
    // 关闭启动画面
    splash.close();
    mainWindow->greet();

    const int ret = QApplication::exec();

    delete fadeIn;
    delete mainWindow;

    return ret;
}