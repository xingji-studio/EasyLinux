//
// Created by cat on 25-7-15.
//

#include <QApplication>
#include <QPropertyAnimation>
#include <QBoxLayout>
#include <QTimer>
#include <QStyle>
#include <QScreen>
#include <QPainter>
#include <QFontDatabase>
// #include <QMovie>

#include "SplashScreen.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"

SplashScreen::SplashScreen(QWidget *parent, const QString &VERSION) : QWidget(parent) {
    // 设置无边框窗口
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 加载自定义字体
    const int fontId = QFontDatabase::addApplicationFont(":/fonts/FiraSans-Bold.ttf");
    const QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    // 创建主布局
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // 应用标题
    auto *titleLabel = new QLabel("EasyLinux", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: white; font-size: 36px; font-weight: bold; }");
    if (!fontFamilies.empty()) {
        QFont font(fontFamilies.at(0));
        font.setPointSize(36);
        titleLabel->setFont(font);
    }
    mainLayout->addWidget(titleLabel);

    // 副标题
    auto *subtitleLabel = new QLabel("(Linux 新手指南)", this);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("QLabel { color: #ecf0f1; font-size: 18px; }");
    mainLayout->addWidget(subtitleLabel);

    // Tux 图片
    auto *tuxLabel = new QLabel(this);
    // auto *tuxMovie = new QMovie(":/pictures/tux.svg", QByteArray(), tuxLabel);
    QPixmap tuxPicture;
    tuxPicture.load(":/pictures/tux.svg");
    tuxPicture = tuxPicture.scaled(200, 200);
    tuxLabel->setPixmap(tuxPicture);
    // tuxLabel->setMovie(tuxMovie);
    tuxLabel->setAlignment(Qt::AlignCenter);
    // tuxLabel->setScaledContents(true); // 缩放
    // tuxMovie->start();
    mainLayout->addWidget(tuxLabel);

    // 进度条
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(12);
    progressBar->setStyleSheet(R"(
        QProgressBar {
            background: rgba(255, 255, 255, 0.2);
            border-radius: 6px;
            border: 1px solid rgba(255, 255, 255, 0.3);
        }
        QProgressBar::chunk {
            background: qlineargradient(
                x1:0, y1:0, x2:1, y2:0,
                stop:0 #3498db, stop:1 #2ecc71
            );
            border-radius: 5px;
        }
    )");
    mainLayout->addWidget(progressBar);

    // 状态文本
    statusLabel = new QLabel("正在启动 EasyLinux...", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("QLabel { color: #ecf0f1; }");
    mainLayout->addWidget(statusLabel);

    // 提示文本
    auto *hintLabel = new QLabel("专为 Linux 新手设计的友好学习环境", this);
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setStyleSheet("QLabel { color: #ecf0f1; font-style: italic; opacity: 0.8; }");
    mainLayout->addWidget(hintLabel);

    // 版本信息
    auto *versionLabel = new QLabel(VERSION, this);
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet("QLabel { color: #ecf0f1; font-size: 12px; opacity: 0.6; }");
    mainLayout->addWidget(versionLabel);

    // 设置窗口大小
    setFixedSize(600, 450);

    // 居中显示
    const QScreen *screen = QApplication::primaryScreen();
    move(screen->geometry().center() - rect().center());
}

void SplashScreen::updateProgress(int value, const QString &status) const {
    progressBar->setValue(value);
    statusLabel->setText(status);
    QApplication::processEvents();
}

void SplashScreen::paintEvent(QPaintEvent *event) {
    // 绘制渐变背景
    QPainter painter(this);
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0, QColor(0x2c3e50));
    gradient.setColorAt(1, QColor(0x4a6491));
    painter.fillRect(rect(), gradient);

    // 绘制装饰元素
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255, 20));
    painter.drawEllipse(width() - 100, -50, 200, 200);
    painter.drawEllipse(-100, height() - 100, 200, 200);

    QWidget::paintEvent(event);
}

#pragma clang diagnostic pop