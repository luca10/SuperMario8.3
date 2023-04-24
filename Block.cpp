#include"Block.h"
#include <QBrush>
#include <QPainter>

Block::Block(QRect rect) : Inert(){

	setPos(QPoint(rect.x(), rect.y()));

	//create collage texture
	QPixmap collage(loadTexture(":/graphics/World8.3/block.png"));
	collage = collage.scaled(rect.width(), rect.height());
	QPainter painter(&collage);
	QPixmap single_block(loadTexture(":/graphics/World8.3/block.png"));
	for (int y = 0; y < rect.height(); y += single_block.height())
		for (int x = 0; x < rect.width(); x += single_block.width())
			painter.drawPixmap(x, y, single_block);
	setPixmap(collage);



}