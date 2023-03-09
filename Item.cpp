#include "Item.h"

#include <QDebug>

Item::Item(ItemType _type, ItemDirection _direction)
{
	m_position = QPoint(0, 0);
	initPoints(_type, _direction);
}

Item::~Item()
{
}

ItemType Item::getType()
{
	return m_type;
}

ItemDirection Item::getDirection()
{
	return m_direction;
}

PointList Item::getPoints()
{
	return m_points;
}

void Item::New(int _randomFactor)
{
	qsrand(_randomFactor);

	//随机初始化方块类型和方向
	ItemType type = (ItemType)(qrand() % ItemType_MAX);
	ItemDirection direction = (ItemDirection)(qrand() % ItemDirection_MAX);
	initPoints(type, direction);
}

void Item::initPoints(ItemType _type, ItemDirection _direction)
{
	QString text = getPointPositionTest(_type, _direction);
	PointList points = testToPointList(text);

	m_points.clear();
	for (QPoint& p : points)
	{
		m_points.append(m_position + p);
	}
	m_type = _type;
	m_direction = _direction;
}

void Item::clearPoint()
{
	m_points.clear();
}

void Item::addPoints(const PointList& points)
{
	for (int i = 0; i < points.size(); ++i)
	{
		if (m_points.contains(points[i]))
		{
			m_points.append(points[i]);
		}
	}
}

bool Item::Contains(QPoint& point)
{
	return m_points.contains(point);
}

bool Item::Contains(int x, int y)
{
	return m_points.contains(QPoint(x, y));
}

void Item::Draw(QPainter& painter, int startX, int startY, int width, int height)
{
	for (int i = 0; i < m_points.size(); ++i)
	{
		QPoint p = m_points[i];
		painter.drawRect(QRect(startX + p.x() * width, startY + p.y() * height, width, height));
	}
}

QString Item::getPointPositionTest(ItemType type, ItemDirection direction)
{
	QString text;
	switch (type)
	{
	case ItemType_Line:
		if (direction == ItemDirection_Up || direction == ItemDirection_Down)
		{
			text = QString("0 0 0 0/") +
				QString("0 0 0 0/") +
				QString("1 1 1 1/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Left || direction == ItemDirection_Right)
		{
			text = QString("0 0 1 0/") +
				QString("0 0 1 0/") +
				QString("0 0 1 0/") +
				QString("0 0 1 0/");
		}
		break;
	case ItemType_T:
		if (direction == ItemDirection_Up)
		{
			text = QString("0 1 0 0/") +
				QString("1 1 1 0/") +
				QString("0 0 0 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Right)
		{
			text = QString("0 1 0 0/") +
				QString("0 1 1 0/") +
				QString("0 1 0 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Down)
		{
			text = QString("0 0 0 0/") +
				QString("1 1 1 0/") +
				QString("0 1 0 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Left)
		{
			text = QString("0 1 0 0/") +
				QString("1 1 0 0/") +
				QString("0 1 0 0/") +
				QString("0 0 0 0/");
		}
		break;
	case ItemType_L1:
		if (direction == ItemDirection_Up)
		{
			text = QString("0 1 0 0/") +
				QString("0 1 0 0/") +
				QString("0 1 1 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Right)
		{
			text = QString("0 0 0 0/") +
				QString("0 1 1 1/") +
				QString("0 1 0 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Down)
		{
			text = QString("0 0 0 0/") +
				QString("0 1 1 0/") +
				QString("0 0 1 0/") +
				QString("0 0 1 0/");
		}
		else if (direction == ItemDirection_Left)
		{
			text = QString("0 0 0 0/") +
				QString("0 0 1 0/") +
				QString("1 1 1 0/") +
				QString("0 0 0 0/");
		}
		break;
	case ItemType_L2:
		if (direction == ItemDirection_Up)
		{
			text = QString("0 0 1 0/") +
				QString("0 0 1 0/") +
				QString("0 1 1 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Right)
		{
			text = QString("0 0 0 0/") +
				QString("0 1 0 0/") +
				QString("0 1 1 1/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Down)
		{
			text = QString("0 0 0 0/") +
				QString("0 1 1 0/") +
				QString("0 1 0 0/") +
				QString("0 1 0 0/");
		}
		else if (direction == ItemDirection_Left)
		{
			text = QString("0 0 0 0/") +
				QString("1 1 1 0/") +
				QString("0 0 1 0/") +
				QString("0 0 0 0/");
		}
		break;
	case ItemType_Square:
		text = QString("1 1 0 0/") +
			QString("1 1 0 0/") +
			QString("0 0 0 0/") +
			QString("0 0 0 0/");
		break;
	case ItemType_Z:
		if (direction == ItemDirection_Up)
		{
			text = QString("0 1 0 0/") +
				QString("0 1 1 0/") +
				QString("0 0 1 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Right)
		{
			text = QString("0 0 0 0/") +
				QString("0 1 1 0/") +
				QString("1 1 0 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Down)
		{
			text = QString("0 0 1 0/") +
				QString("0 1 1 0/") +
				QString("0 1 0 0/") +
				QString("0 0 0 0/");
		}
		else if (direction == ItemDirection_Left)
		{
			text = QString("0 0 0 0/") +
				QString("1 1 0 0/") +
				QString("0 1 1 0/") +
				QString("0 0 0 0/");
		}
		break;
	case ItemType_MAX:
		break;
	default:
		break;
	}
	return text;
}

PointList Item::testToPointList(QString strFormat)
{
	PointList points;
	QStringList rows = strFormat.split('/');
	for (int i = 0; i < rows.size(); ++i)
	{
		QString strRowText = rows.at(i);
		QStringList columns = strRowText.split(' ');
		for (int j = 0; j < columns.size(); ++j)
		{
			if (columns.at(j) == "1")
			{
				points.append(QPoint(i, j));
			}
		}
	}
	return points;
}

void Item::changeDirection(int direction)
{
	ItemDirection newDirection = (ItemDirection)((m_direction + direction) % ItemDirection_MAX);
	initPoints(m_type, newDirection);
}

void Item::move(int x, int y)
{
	for (int i = 0; i < m_points.size(); ++i)
	{
		int x1 = m_points[i].x() + x;
		int y1 = m_points[i].y() + y;
		m_points[i].setX(x1);
		m_points[i].setY(y1);
	}
	m_position += QPoint(x, y);
}

void Item::moveTo(int x, int y)
{
	for (int i = 0; i < m_points.size(); ++i)
	{
		int x1 = m_points[i].x() - m_position.x() + x;
		int y1 = m_points[i].y() - m_position.y() + y;
		m_points[i].setX(x1);
		m_points[i].setY(y1);
	}
	m_position += QPoint(x, y);
}

void Item::moveDown(int nRow, int y)
{
	for (int i = 0; i < m_points.size(); ++i)
	{
		if (m_points[i].y() < nRow)
		{
			m_points[i].setY(m_points[i].y() + y);
		}
	}
}

void Item::deleteRow(int y)
{
	PointList newPoints;
	for (int i = 0; i < m_points.size(); ++i)
	{
		if (m_points[i].y() != y)
		{
			newPoints.append(m_points[i]);
		}
	}
	m_points = newPoints;
}
