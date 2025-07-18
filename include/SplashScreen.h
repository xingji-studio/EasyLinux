//
// Created by cat on 25-7-15.
//

#pragma once

#include <QLabel>
#include <QProgressBar>

class SplashScreen final : public QWidget {
public:
    explicit SplashScreen(QWidget *parent = nullptr);
    void updateProgress(const int value, const QString &status) const;

private:
    QProgressBar *progressBar;
    QLabel *statusLabel;

protected:
    void paintEvent(QPaintEvent *event) override;
};
