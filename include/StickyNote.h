#pragma once

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QBoxLayout>

class StickyNote {
private:
    QLabel* master;
public:
    StickyNote(QWidget* parent, QBoxLayout* layout, QString& text);
    void setText(QString& text);
};

