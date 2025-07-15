#include <QApplication>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QLabel>
#include <QProgressBar>
#include <QBoxLayout>
#include <QTimer>
#include <QStyle>
#include <QScreen>
#include <QPainter>
#include <QLinearGradient>
#include <QFontDatabase>
#include <QMovie>
#include <QThread>

class SplashScreen : public QWidget {
public:
    SplashScreen(QWidget *parent = nullptr) : QWidget(parent) {
        // 设置无边框窗口
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

        // 加载自定义字体
        int fontId = QFontDatabase::addApplicationFont(":/fonts/FiraSans-Bold.ttf");
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

        // 创建主布局
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(40, 40, 40, 40);
        mainLayout->setSpacing(20);

        // 应用标题
        QLabel *titleLabel = new QLabel("EasyLinux", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("QLabel { color: white; font-size: 36px; font-weight: bold; }");
        if (!fontFamilies.empty()) {
            QFont font(fontFamilies.at(0));
            font.setPointSize(36);
            titleLabel->setFont(font);
        }
        mainLayout->addWidget(titleLabel);

        // 副标题
        QLabel *subtitleLabel = new QLabel("Linux 新手指南", this);
        subtitleLabel->setAlignment(Qt::AlignCenter);
        subtitleLabel->setStyleSheet("QLabel { color: #ecf0f1; font-size: 18px; }");
        mainLayout->addWidget(subtitleLabel);

        // Tux 动画
        QLabel *tuxLabel = new QLabel(this);
        QMovie *tuxMovie = new QMovie(":/animations/tux.gif", QByteArray(), tuxLabel);
        tuxLabel->setMovie(tuxMovie);
        tuxLabel->setAlignment(Qt::AlignCenter);
        tuxMovie->start();
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
        QLabel *hintLabel = new QLabel("专为 Linux 新手设计的友好学习环境", this);
        hintLabel->setAlignment(Qt::AlignCenter);
        hintLabel->setStyleSheet("QLabel { color: #ecf0f1; font-style: italic; opacity: 0.8; }");
        mainLayout->addWidget(hintLabel);

        // 版本信息
        QLabel *versionLabel = new QLabel("版本 1.0 · 基于 Qt 6.5", this);
        versionLabel->setAlignment(Qt::AlignCenter);
        versionLabel->setStyleSheet("QLabel { color: #ecf0f1; font-size: 12px; opacity: 0.6; }");
        mainLayout->addWidget(versionLabel);

        // 设置窗口大小
        setFixedSize(600, 450);

        // 居中显示
        QScreen *screen = QApplication::primaryScreen();
        move(screen->geometry().center() - rect().center());
    }

    void updateProgress(int value, const QString &status) {
        progressBar->setValue(value);
        statusLabel->setText(status);
        QApplication::processEvents(); // 确保UI更新
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        // 绘制渐变背景
        QPainter painter(this);
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor("#2c3e50"));
        gradient.setColorAt(1, QColor("#4a6491"));
        painter.fillRect(rect(), gradient);

        // 绘制装饰元素
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 255, 255, 20));
        painter.drawEllipse(width() - 100, -50, 200, 200);
        painter.drawEllipse(-100, height() - 100, 200, 200);

        QWidget::paintEvent(event);
    }

private:
    QProgressBar *progressBar;
    QLabel *statusLabel;
};

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("EasyLinux - Linux 新手指南");
        resize(1000, 700);

        // 创建主部件
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        // 创建标题栏
        QWidget *header = new QWidget(centralWidget);
        header->setFixedHeight(60);
        header->setStyleSheet("background: #3498db;");

        QHBoxLayout *headerLayout = new QHBoxLayout(header);
        headerLayout->setContentsMargins(20, 0, 20, 0);

        QLabel *titleLabel = new QLabel("EasyLinux", header);
        titleLabel->setStyleSheet("QLabel { color: white; font-size: 20px; font-weight: bold; }");
        headerLayout->addWidget(titleLabel);

        headerLayout->addStretch();

        QLabel *subtitleLabel = new QLabel("Linux 学习助手", header);
        subtitleLabel->setStyleSheet("QLabel { color: rgba(255,255,255,0.8); }");
        headerLayout->addWidget(subtitleLabel);

        // 主内容区域
        QWidget *contentWidget = new QWidget(centralWidget);
        QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
        contentLayout->setContentsMargins(40, 40, 40, 40);

        QLabel *welcomeLabel = new QLabel("欢迎使用 EasyLinux", contentWidget);
        welcomeLabel->setStyleSheet("QLabel { font-size: 28px; font-weight: bold; color: #2c3e50; }");
        contentLayout->addWidget(welcomeLabel);

        QLabel *descriptionLabel = new QLabel(
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
        QWidget *cardsWidget = new QWidget(contentWidget);
        QHBoxLayout *cardsLayout = new QHBoxLayout(cardsWidget);
        cardsLayout->setSpacing(20);

        auto createCard = [](const QString &title, const QString &desc, const QColor &color) {
            QWidget *card = new QWidget;
            card->setStyleSheet(QString(
                "QWidget { background: white; border-radius: 10px; }"
                "QLabel { padding: 15px; }"
            ));

            QVBoxLayout *cardLayout = new QVBoxLayout(card);

            QLabel *titleLabel = new QLabel(title, card);
            titleLabel->setStyleSheet(QString("font-size: 18px; font-weight: bold; color: %1;").arg(color.name()));
            cardLayout->addWidget(titleLabel);

            QLabel *descLabel = new QLabel(desc, card);
            descLabel->setWordWrap(true);
            descLabel->setStyleSheet("color: #7f8c8d;");
            cardLayout->addWidget(descLabel);

            return card;
        };

        cardsLayout->addWidget(createCard(
            "命令学习",
            "通过交互式终端学习常用 Linux 命令",
            QColor("#e74c3c")
        ));

        cardsLayout->addWidget(createCard(
            "文件系统",
            "理解 Linux 文件系统结构与权限管理",
            QColor("#3498db")
        ));

        cardsLayout->addWidget(createCard(
            "软件管理",
            "掌握软件安装、更新和包管理工具",
            QColor("#2ecc71")
        ));

        contentLayout->addWidget(cardsWidget);

        // 添加到主布局
        mainLayout->addWidget(header);
        mainLayout->addWidget(contentWidget, 1);

        setCentralWidget(centralWidget);

        // 初始设置为透明
        setWindowOpacity(0.0);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建启动画面
    SplashScreen splash;
    splash.show();

    // 强制立即显示
    app.processEvents();

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
        int stepIndex = qMin(i / 20, loadingSteps.size() - 1);
        splash.updateProgress(i, loadingSteps[stepIndex]);
        QThread::msleep(50); // 暂停50毫秒
        app.processEvents(); // 处理事件循环
    }

    // 创建主窗口
    MainWindow mainWindow;

    // 添加淡入动画
    QPropertyAnimation *fadeIn = new QPropertyAnimation(&mainWindow, "windowOpacity");
    fadeIn->setDuration(800);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::OutCubic);

    // 显示主窗口并启动动画
    mainWindow.show();
    fadeIn->start();

    // 关闭启动画面
    splash.close();

    return app.exec();
}