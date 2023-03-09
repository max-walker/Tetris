#pragma once

#include "Item.h"
#include <QWidget>

class GameArea : public QWidget
{
	Q_OBJECT

public:
	explicit GameArea(QWidget* parent = nullptr);

	void DrawBKRects();
	void DrawFixedRects();
	void DrawCurItem();

	void NewGame();
	void KeyPressed(int key);

	bool HitSide();
	bool HitBottom();
	bool HitTop();
	void AddToFixedRects();
	void DeleteFullRows();

	int GetLevelTime(int level);

signals:
	void sigUpdateNextItem(ItemType type, ItemDirection direction);
	void sigUpdateScore(int score);
	void sigUpdateLevel(int speed);
	void sigPause(bool paused);

protected:
	void paintEvent(QPaintEvent* event) override;
	void timerEvent(QTimerEvent* event) override;

private:
	Item m_fixItems;  //已经固定的方块
	Item m_curItem;   //正在控制的方块
	Item m_nextItem;  //下一个方块

	int m_timerID;
	int m_level;
	int m_score;
	bool m_paused;
};

