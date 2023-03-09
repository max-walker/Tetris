#include "NextArea.h"

NextArea::NextArea(QWidget* parent)
	: QWidget(parent)
{
}

void NextArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setBrush(QColor("#FFDEAD"));
	painter.setPen(QPen(QColor(Qt::black), 1));

	int xStart = 80;
	int yStart = 10;
	int w = 20, h = 20;
	for (QPoint& p : m_item.getPoints())
	{
		int x = xStart + p.x() * w;
		int y = yStart + p.y() * h;
		painter.drawRect(x, y, w, h);
	}
	update();
}

void NextArea::slotUpdateNextItem(ItemType t, ItemDirection direction)
{
	m_item.initPoints(t, direction);
}
