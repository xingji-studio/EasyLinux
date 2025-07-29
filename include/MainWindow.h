//
// Created by cat on 25-7-15.
//

#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QString>

class MainWindow : public QMainWindow {
private:
    QLabel *p_welcomeLabel;
    QLabel *p_descriptionLabel;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setWelecomeLabelText(QString& newText);
    void setDescriptionLabelText(QString& newText);
};
