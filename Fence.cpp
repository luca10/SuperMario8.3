#include "Fence.h"
#include <QBrush>
#include <QPainter>

Fence::Fence(QRect rect) : Inert()
{
	// set position
	setPos(QPoint(rect.x(), rect.y()));
	collidable = false;
	// create collage texture
	QPixmap collage(loadTexture(":/graphics/World8.3/fence.bmp"));
	collage = collage.scaled(rect.width(), rect.height());
	QPainter painter(&collage);
	QPixmap single_block(loadTexture(":/graphics/World8.3/fence.bmp"));
	for (int y = 0; y < rect.height(); y += single_block.height())
		for (int x = 0; x < rect.width(); x += single_block.width())
			painter.drawPixmap(x, y, single_block);
	setPixmap(collage);

	// set a high z-value so it is displayed on top of other objects
	//setZValue(2);
}
