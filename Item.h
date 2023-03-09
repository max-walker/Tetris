#pragma once

#include <QPoint>
#include <QList>
#include <QMap>
#include <QPainter>
#include <QString>

// 各种类型的俄罗斯方块
enum ItemType {
	ItemType_Line = 0,
	ItemType_T,
	ItemType_L1,
	ItemType_L2,
	ItemType_Square,
	ItemType_Z,
	ItemType_MAX
};

//旋转时候的各个方向（顺时针旋转）
enum ItemDirection {
	ItemDirection_Up = 0,
	ItemDirection_Right,
	ItemDirection_Down,
	ItemDirection_Left,
	ItemDirection_MAX
};

using PointList = QList<QPoint>;

class Item
{
public:
	Item() {}
	Item(ItemType _type, ItemDirection _direction);
	~Item();

	ItemType getType();
	ItemDirection getDirection();
	PointList getPoints();

	void New(int _randomFactor);
	void initPoints(ItemType _type, ItemDirection _direction);
	void clearPoint();
	void addPoints(const PointList& points);
	bool Contains(QPoint& point);
	bool Contains(int x, int y);
	void changeDirection(int direction);
	void move(int x, int y);
	void moveTo(int x, int y);
	void moveDown(int nRow, int y);
	void deleteRow(int y);

	void Draw(QPainter& painter, int startX, int startY, int width, int height);

private:
	QString getPointPositionTest(ItemType type, ItemDirection direction);
	PointList testToPointList(QString strFormat);

private:
	ItemType m_type;
	ItemDirection m_direction;
	QPoint m_position;
	PointList m_points;
};

