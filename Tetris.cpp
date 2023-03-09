#include "Tetris.h"

Tetris::Tetris(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setFixedSize(1000, 800);

    connect(ui.widgetGameArea, &GameArea::sigUpdateScore, this, &Tetris::slotUpdateScore);
	connect(ui.widgetGameArea, &GameArea::sigUpdateLevel, this, &Tetris::slotUpdateLevel);
    connect(ui.widgetGameArea, &GameArea::sigUpdateNextItem, ui.widgetNextArea, &NextArea::slotUpdateNextItem);

    ui.widgetGameArea->NewGame();
}

void Tetris::keyPressEvent(QKeyEvent * e)
{
    ui.widgetGameArea->KeyPressed(e->key());
    QMainWindow::keyPressEvent(e);
}

void Tetris::slotUpdateLevel(int speed)
{
    ui.label_speed->setText(QString::number(speed));
}

void Tetris::slotUpdateScore(int score)
{
    ui.label_score->setText(QString::number(score));
}

