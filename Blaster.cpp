#include "Blaster.h"


Blaster::Blaster(QPoint Position, int size) {

	//Texture in base alla grandezza del canone
	if (size == 0)
		setPixmap(QPixmap(loadTexture(":/graphics/World8.3/blaster_small.bmp")));
	else
		setPixmap(QPixmap(loadTexture(":/graphics/World8.3/blaster_big.bmp"))); 
     setPos(Position - QPoint(0, pixmap().height()));
	 //setZValue(0);
	 collidable = true;
	
}