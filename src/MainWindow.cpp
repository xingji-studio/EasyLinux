//
// Created by cat on 25-7-15.
//

#include <QLabel>
#include <QBoxLayout>
#include <QPainter>
#include <QFontDatabase>


#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("EasyLinux - Linux 新手指南");
    resize(1000, 700);

    // 创建主部件
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 创建标题栏
    auto *header = new QWidget(centralWidget);
    header->setFixedHeight(60);
    header->setStyleSheet("background: #3498db;");

    auto *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(20, 0, 20, 0);

    auto *titleLabel = new QLabel("EasyLinux", header);
    titleLabel->setStyleSheet("QLabel { color: white; font-size: 20px; font-weight: bold; }");
    headerLayout->addWidget(titleLabel);

    headerLayout->addStretch();

    auto *subtitleLabel = new QLabel("Linux 学习助手", header);
    subtitleLabel->setStyleSheet("QLabel { color: rgba(255,255,255,0.8); }");
    headerLayout->addWidget(subtitleLabel);

    // 主内容区域
    auto *contentWidget = new QWidget(centralWidget);
    auto *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(40, 40, 40, 40);

    auto *welcomeLabel = new QLabel("欢迎使用 EasyLinux", contentWidget);
    welcomeLabel->setStyleSheet("QLabel { font-size: 28px; font-weight: bold; color: #2c3e50; }");
    contentLayout->addWidget(welcomeLabel);

    auto *descriptionLabel = new QLabel(
        "无论您是刚接触 Linux 的新手，还是从 Windows 转来的用户，"
        "EasyLinux 都旨在为您提供最友好的学习体验。\n\n"
        "通过互动教程、命令行模拟器和实时帮助，"
        "您将快速掌握 Linux 的核心概念和日常操作。",
        contentWidget
    );
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setStyleSheet("QLabel { font-size: 16px; color: #34495e; line-height: 1.5; }");
    contentLayout->addWidget(descriptionLabel);

    contentLayout->addStretch();

    // 功能卡片布局
    auto *cardsWidget = new QWidget(contentWidget);
    auto *cardsLayout = new QHBoxLayout(cardsWidget);
    cardsLayout->setSpacing(20);

    auto createCard = [](const QString &title, const QString &desc, const QColor &color) -> QWidget* {
        auto *card = new QWidget();
        card->setStyleSheet(QString(
            "QWidget { background: white; border-radius: 10px; }"
            "QLabel { padding: 15px; }"
        ));

        auto *cardLayout = new QVBoxLayout(card);

        auto *titleLabel = new QLabel(title, card);
        titleLabel->setStyleSheet(QString("font-size: 18px; font-weight: bold; color: %1;").arg(color.name()));
        cardLayout->addWidget(titleLabel);

        auto *descLabel = new QLabel(desc, card);
        descLabel->setWordWrap(true);
        descLabel->setStyleSheet("color: #7f8c8d;");
        cardLayout->addWidget(descLabel);

        return card;
    };

    cardsLayout->addWidget(createCard(
        "命令学习",
        "通过交互式终端学习常用 Linux 命令",
        QColor(0xe74c3c)
    ));

    cardsLayout->addWidget(createCard(
        "文件系统",
        "理解 Linux 文件系统结构与权限管理",
        QColor(0x3498db)
    ));

    cardsLayout->addWidget(createCard(
        "软件管理",
        "掌握软件安装、更新和包管理工具",
        QColor(0x2ecc71)
    ));

    contentLayout->addWidget(cardsWidget);

    // 添加到主布局
    mainLayout->addWidget(header);
    mainLayout->addWidget(contentWidget, 1);

    setCentralWidget(centralWidget);

    // 初始设置为透明
    setWindowOpacity(0.0);
}

