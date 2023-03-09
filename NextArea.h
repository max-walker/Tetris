#pragma once

#include "Item.h"
#include <QWidget>

class NextArea : public QWidget
{
	Q_OBJECT

public:
	explicit NextArea(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* event) override;

public slots:
	void slotUpdateNextItem(ItemType t, ItemDirection direction);

private:
	Item m_item;
};

