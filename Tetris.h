#pragma once

#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include "ui_Tetris.h"

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = nullptr);
    ~Tetris() {}

protected:
    void keyPressEvent(QKeyEvent* e) override;

private slots:
    void slotUpdateScore(int score);
    void slotUpdateLevel(int speed);

private:
    Ui::TetrisClass ui;
};
