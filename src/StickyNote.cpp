#include "StickyNote.h"

StickyNote::StickyNote(QWidget *parent, QBoxLayout* layout, QString &text) {
    this->master = new QLabel(parent);

    this->master->setText(text);
    this->master->setStyleSheet("border:2px solid #3498db; "
                                "border-radius: 6px; ");

    layout->addWidget(this->master);
}