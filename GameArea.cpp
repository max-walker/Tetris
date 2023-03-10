#include "GameArea.h"
#include <QTimerEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTime>

//默认游戏区域为15*20个单元格，每个单元格尺寸为40*40像素
#define MAX_COLUME   15
#define MAX_ROW      20
#define RECT_WIDTH   40
#define RECT_HEIGHT  40

//默认中间出生位置
#define DEFAULT_X_POS  (MAX_COLUME / 2 -1)

GameArea::GameArea(QWidget* parent)
	: QWidget(parent)
	, m_score(0)
	, m_level(1)
	, m_paused(false)
{
	setMinimumSize(MAX_COLUME * RECT_WIDTH, MAX_ROW * RECT_HEIGHT);
}

void GameArea::DrawBKRects()
{
	QPainter painter(this);
	painter.setBrush(QColor("#696969"));
	painter.setPen(Qt::NoPen);

	for (int i = 0; i < MAX_COLUME; ++i)
	{
		for (int j = 0; j < MAX_ROW; ++j)
		{
			if (i == 0 || i == MAX_COLUME - 1 || j == 0 || j == MAX_ROW - 1)
			{
				painter.drawRect(i * RECT_WIDTH, j * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT);
			}
		}
	}
}

void GameArea::DrawFixedRects()
{
	QPainter painter(this);
	painter.setBrush(QColor("#D3D3D3"));
	painter.setPen(QPen(QColor(Qt::black), 1));

	m_fixItems.Draw(painter, 0, 0, RECT_WIDTH, RECT_HEIGHT);
}

void GameArea::DrawCurItem()
{
	QPainter painter(this);
	painter.setBrush(QColor("#FFDEAD"));
	painter.setPen(QPen(QColor(Qt::black), 1));

	m_curItem.Draw(painter, 0, 0, RECT_WIDTH, RECT_HEIGHT);
}

void GameArea::NewGame()
{
	m_fixItems.clearPoint();

	m_curItem.New(QTime::currentTime().msec());
	m_curItem.moveTo(DEFAULT_X_POS, 1);
	m_nextItem.New(QTime::currentTime().second());
	emit sigUpdateNextItem(m_nextItem.getType(), m_nextItem.getDirection());

	m_score = 0;
	m_level = 1;
	m_timerID = startTimer(GetLevelTime(m_level));
}

void GameArea::KeyPressed(int key)
{
	int x = 0, y = 0;
	switch (key)
	{
	case Qt::Key_Left:
		x = -1;
		break;
	case Qt::Key_Up:
		m_curItem.changeDirection(1);
		if (HitSide() || HitBottom())
		{
			m_curItem.changeDirection(-1);
		}
		break;
	case Qt::Key_Right:
		x = 1;
		break;
	case Qt::Key_Down:
		y = 1;
		break;
	case Qt::Key_Space:
	{
		while (1)
		{
			m_curItem.move(0, 1);
			if (HitSide() || HitBottom())
			{
				m_curItem.move(0, -1);
				break;
			}
		}
		return;
	}
	case Qt::Key_Return:
	case Qt::Key_Enter:
		m_paused = !m_paused;
		break;
	default:
		break;
	}
	m_curItem.move(x, y);
	if (HitSide() || HitBottom())
	{
		m_curItem.move(-x, -y);
	}
}

bool GameArea::HitSide()
{
	for (QPoint p : m_curItem.getPoints())
	{
		if (p.x() <= 0 || p.x() >= MAX_COLUME - 1)
		{
			return true;
		}
	}
	return false;
}

bool GameArea::HitBottom()
{
	for (QPoint p : m_curItem.getPoints())
	{
		if (p.y() >= MAX_ROW - 1)
		{
			return true;
		}
		if (m_fixItems.Contains(p))
		{
			return true;
		}
	}
	return false;
}

bool GameArea::HitTop()
{
	for (QPoint p : m_fixItems.getPoints())
	{
		if (p.y() <= 1)
		{
			return true;
		}
	}
	return false;
}

void GameArea::AddToFixedRects()
{
	PointList points = m_curItem.getPoints();
	m_fixItems.addPoints(points);
}

void GameArea::DeleteFullRows()
{
	int rowDeleted = 0;
	for (int i = 1; i < MAX_ROW - 1; ++i)
	{
		int count = 0;
		for (int j = 1; j < MAX_COLUME - 1; ++j)
		{
			if (m_fixItems.Contains(j, i))
			{
				++count;
			}
		}
		if (count >= MAX_COLUME - 2)
		{
			m_fixItems.deleteRow(i);
			m_fixItems.moveDown(i, 1);
			++rowDeleted;
		}
	}

	if (rowDeleted == 1)
	{
		m_score += 100;
	}
	else if (rowDeleted == 2)
	{
		m_score += 300;
	}
	else if (rowDeleted == 3)
	{
		m_score += 500;
	}
	else if (rowDeleted == 4)
	{
		m_score += 700;
	}
	emit sigUpdateScore(m_score);

	if (m_score >= 1000 * m_level)
	{
		++m_level;

		killTimer(m_timerID);
		m_timerID = startTimer(GetLevelTime(m_level));
		emit sigUpdateLevel(m_level);
	}
}

int GameArea::GetLevelTime(int level)
{
	if (level > 8)
	{
		return 200;
	}
	return (11 - level) * 100;
}

void GameArea::paintEvent(QPaintEvent* event)
{
	DrawBKRects();
	DrawFixedRects();
	DrawCurItem();

	if (m_paused)
	{
		QFont font;
		font.setPixelSize(100);

		QPainter painter(this);
		painter.setFont(font);
		painter.setBrush(Qt::NoBrush);
		painter.setPen(QPen(QColor("#FF3333"), 1));
		painter.drawText(rect(), Qt::AlignCenter, "Pause");
	}
	update();
}

void GameArea::timerEvent(QTimerEvent* event)
{
	if (m_paused)
	{
		return;
	}

	if (event->timerId() == m_timerID)
	{
		m_curItem.move(0, 1);
		if (HitBottom())
		{
			m_curItem.move(0, -1);
			AddToFixedRects();
			DeleteFullRows();

			if (HitTop())
			{
				killTimer(m_timerID);
				QMessageBox::information(nullptr, "GAME OVER", "GAME OVER", QMessageBox::Yes, QMessageBox::Yes);
				NewGame();
				return;
			}

			m_curItem = m_nextItem;
			m_curItem.moveTo(DEFAULT_X_POS, 1);
			m_nextItem.New(QTime::currentTime().msec());
			emit sigUpdateNextItem(m_nextItem.getType(), m_nextItem.getDirection());
		}
	}
}
