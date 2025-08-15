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

#include <QLabel>
#include <QBoxLayout>
#include <QPainter>
#include <QFontDatabase>
#include <QPushButton>
#include <memory>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QErrorMessage>

#include "MainWindow.h"
#include "StickyNote.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"


int getFileLineCount(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件:" << file.errorString();
        return -1;
    }

    QTextStream in(&file);
    int lineCount = 0;

    // 高效读取方式：使用 readLine() 但不存储内容
    while (!in.atEnd()) {
        in.readLine();
        lineCount++;
    }

    file.close();
    return lineCount;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle(tr("EasyLinux - Linux 新手指南"));
    this->resize(1000, 700);

    // 创建主部件
    auto *centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background: black");
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

//    auto *subtitleLabel = new QLabel("Linux 学习助手", header);
//    subtitleLabel->setStyleSheet("QLabel { color: rgba(255,255,255,0.8); }");
//    headerLayout->addWidget(subtitleLabel);

    auto *settingsButton = new QPushButton("选项 ⚙\uFE0F", header);
    settingsButton->setStyleSheet("QPushButton { "
                                  "border:0px solid #ffffff; "
                                  "border-radius: 6px; "
                                  "} QPushButton:hover {"
                                  "background-color: #111111; "
                                  "color: white; "
                                  "}");


    headerLayout->addWidget(settingsButton);

    // 主内容区域
    auto *contentWidget = new QWidget(centralWidget);
    auto *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(40, 40, 40, 40);

    this->p_welcomeLabel = new QLabel("欢迎使用 EasyLinux", contentWidget);
    this->p_welcomeLabel->setStyleSheet("QLabel { font-size: 28px; font-weight: bold; color: #5DADE2 }");
    contentLayout->addWidget(this->p_welcomeLabel);

    this->p_descriptionLabel = new QLabel(
        tr("无论您是刚接触 Linux 的新手，还是从 Windows 转来的用户，"
        "EasyLinux 都旨在为您提供最友好的学习体验。\n\n"
        "通过互动教程、命令行模拟器和实时帮助，"
        "您将快速掌握 Linux 的核心概念和日常操作。"),
        contentWidget
    );
    this->p_descriptionLabel->setWordWrap(true);
    this->p_descriptionLabel->setStyleSheet("QLabel { font-size: 16px;  line-height: 1.5; color: #5DADE2; }");
    contentLayout->addWidget(this->p_descriptionLabel);

    contentLayout->addStretch();
    auto *startWidget = new QWidget(contentWidget);
    auto *startLayout = new QHBoxLayout(startWidget);

    auto *archLinuxLabel = new QLabel(startWidget);
    QPixmap archLinuxPic;
    archLinuxPic.load(":/pictures/Archlinux.png");
    archLinuxPic = archLinuxPic.scaled(388, 500);
    archLinuxLabel->setPixmap(archLinuxPic);
    archLinuxLabel->setAlignment(Qt::AlignCenter);
    startLayout->addWidget(archLinuxLabel);

    auto *buttonAndNotesWidget = new QWidget(startWidget);
    auto *buttonAndNotesLayout = new QVBoxLayout(buttonAndNotesWidget);

    QString noteText = "Test";
    std::unique_ptr<StickyNote>
    stickyNote(new StickyNote(buttonAndNotesWidget, buttonAndNotesLayout, noteText));

    auto *startButton = new QPushButton(tr("启动！"), buttonAndNotesWidget);
    startButton->setStyleSheet("QPushButton { "
                             "border:2px solid #3498db; "
                             "border-radius: 6px;"
                             "min-width: 10px;"   // 最小宽度
                             "min-height: 10px;"   // 最小高度
                             "max-height: 80px;"
                             "font-size: 30px"
                             "} QPushButton:hover {"
                             "background-color: #111111; "
                             "color: white; "
                             "}");
    buttonAndNotesLayout->addWidget(startButton);
    startLayout->addWidget(buttonAndNotesWidget);
    contentLayout->addWidget(startWidget);



    // 功能卡片布局
//    auto *cardsWidget = new QWidget(contentWidget);
//    auto *cardsLayout = new QHBoxLayout(cardsWidget);
//    cardsLayout->setSpacing(20);

//    auto createCard = [](const QString &title, const QString &desc, const QColor &color) -> QWidget* {
//        auto *card = new QWidget();
//        card->setStyleSheet(QString(
//            "QWidget { background: white; border-radius: 10px; }"
//            "QLabel { padding: 15px; }"
//        ));
//
//        auto *cardLayout = new QVBoxLayout(card);
//
//        auto *titleLabel = new QLabel(title, card);
//        titleLabel->setStyleSheet(QString("font-size: 18px; font-weight: bold; color: %1;").arg(color.name()));
//        cardLayout->addWidget(titleLabel);
//
//        auto *descLabel = new QLabel(desc, card);
//        descLabel->setWordWrap(true);
//        descLabel->setStyleSheet("color: #7f8c8d;");
//        cardLayout->addWidget(descLabel);
//
//        return card;
//    };

//    cardsLayout->addWidget(createCard(
//        "命令学习",
//        "通过交互式终端学习常用 Linux 命令",
//        QColor(0xe74c3c)
//    ));
//
//    cardsLayout->addWidget(createCard(
//        "文件系统",
//        "理解 Linux 文件系统结构与权限管理",
//        QColor(0x3498db)
//    ));
//
//    cardsLayout->addWidget(createCard(
//        "软件管理",
//        "掌握软件安装、更新和包管理工具",
//        QColor(0x2ecc71)
//    ));
//
//    contentLayout->addWidget(cardsWidget);

    // 添加到主布局
    mainLayout->addWidget(header);
    mainLayout->addWidget(contentWidget, 1);

    setCentralWidget(centralWidget);

    // 初始设置为透明
    // setWindowOpacity(0.0);
}

void MainWindow::setWelcomeLabelText(QString& newText) {
    this->p_welcomeLabel->setText(newText);
}

void MainWindow::setDescriptionLabelText(QString& newText) {
    this->p_descriptionLabel->setText(newText);
}

void MainWindow::greet() {
    int launchedTimes;
    QString userName;

    QFile file("config.json");
    if (file.open(QIODevice::ReadWrite)) { // 读取文件，解析出启动次数
        QByteArray data = file.readAll();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);

        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject config = doc.object();
            launchedTimes = config["TIMES"].toInt();
            userName = config["NAME"].toString();
            file.seek(0);
            config["TIMES"] = launchedTimes + 1;
            QJsonDocument newDoc(config);
            file.write(newDoc.toJson());
            file.resize(file.pos());
        } else { // 未找 config.json 到或文件格式错误
            qDebug() << "MainWindow::greet() err:" << error.errorString();
            // 创建 JSON 对象并插入数据
            QJsonObject config;
            config["TIMES"] = 1;
            bool ok;
            QString text = QInputDialog::getText(
                    this,                 // 父窗口
                    tr("尊姓大名?"),             // 对话框标题
                    tr("用户名:"),            // 提示文本
                    QLineEdit::Normal,            // 输入模式
                    tr(""),                 // 默认文本
                    &ok                           // 返回用户是否点击OK
            );

            if (ok) {
                config["NAME"] = text;
            }
            // 将对象转为 JSON 文档并保存
            QJsonDocument doc(config);
            QFile file("config.json");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(doc.toJson()); // 默认带缩进格式
                file.close();
            }
            return;
        }
    }
    int indexOfGreetingWords = QRandomGenerator::global()->bounded(0, getFileLineCount("greetings.txt"));
    QFile greetings("greetings.txt");
    if (greetings.open(QIODevice::ReadOnly)) {
        QString greetingWord = greetings.readAll();
        // qDebug() << greetingWord;
        QStringList greetingWordsList = greetingWord.split("\n");
        this->setWelcomeLabelText(greetingWordsList[indexOfGreetingWords]);
    }

#define SUCCESS 0

    if (system("fortune > ./fortune_words.txt") == SUCCESS) {
        QFile fortuneWords("fortune_words.txt");
        if (fortuneWords.open(QIODevice::ReadOnly)) {
            QString readFortuneWords = fortuneWords.readAll();
            readFortuneWords = "\n\n" + readFortuneWords;
            this->setDescriptionLabelText(readFortuneWords);
        }
    } else {
        QErrorMessage fileNotFound(this);
        fileNotFound.showMessage(
                tr("This application depends on the following applications for correct operation. "
                   "\n \t fortune.You can try to install it with your package manager"));
        fileNotFound.exec();
    }
}

#pragma clang diagnostic pop