#include "Castel.h"
#include "qdebug.h"
#include <QBrush>
#include <QPainter>

Castel::Castel(QRect rect, int size) : Inert()
{
	if (size == 0) {
		// set position
		setPos(QPoint(rect.x(), rect.y()));
		collidable = false;
		// create collage texture
		QPixmap collage(loadTexture(":/graphics/World8.3/castle0_brick.bmp"));
		collage = collage.scaled(rect.width(), rect.height());
		QPainter painter(&collage);

		QPixmap single_block(loadTexture(":/graphics/World8.3/castle0_brick.bmp"));

		for (int y = 0; y < rect.height(); y += single_block.height())
			for (int x = 0; x < rect.width(); x += single_block.width())
				painter.drawPixmap(x, y, single_block);

		setPixmap(collage);		
		
	}
	if (size == 1) {
		// set position
		setPos(QPoint(rect.x(), rect.y()));
		collidable = false;
		// create collage texture
		QPixmap collage(loadTexture(":/graphics/World8.3/sky.png"));
		collage = collage.scaled(rect.width(), rect.height());
		QPainter painter(&collage);

		QPixmap single_block(loadTexture(":/graphics/World8.3/castle0_top1.bmp"));

		for (int y = 0; y < rect.height(); y += single_block.height())
			for (int x = 0; x < rect.width(); x += single_block.width())
				painter.drawPixmap(x, y, single_block);
	
		setPixmap(collage);
	
	}
	if (size == 2) {
		// set position
		setPos(QPoint(rect.x(), rect.y()));
		collidable = false;
		// create collage texture
		QPixmap collage(loadTexture(":/graphics/World8.3/sky.png"));
		collage = collage.scaled(rect.width(), rect.height());
		QPainter painter(&collage);

		QPixmap single_block(loadTexture(":/graphics/World8.3/castle0_top0.bmp"));

		for (int y = 0; y < rect.height(); y += single_block.height())
			for (int x = 0; x < rect.width(); x += single_block.width())
				painter.drawPixmap(x, y, single_block);

		setPixmap(collage);

	}
}