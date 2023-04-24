#include "Pipe.h"
#include "Mario.h"
#include "Game.h"
#include "Object.h"
#include "Terrain.h"
#include <QSound>

#include <QDebug>
#include <QObject>

Pipe::Pipe(QPoint Position,int size) {

	//control block that choose the right texture depending on the size
	if (size == 0)
		setPixmap(QPixmap(loadTexture(":/graphics/World8.3/pipe-small.png")));
	if (size == 1)
		setPixmap(QPixmap(loadTexture(":/graphics/World8.3/pipe-med.png")));
	if(size==3)
	    setPixmap(QPixmap(loadTexture(":/graphics/World8.3/pipe-big.png")));

	collidable = true;

	//set the position of the pipe 
	setPos(Position - QPoint(16, pixmap().height()));
	setZValue(2);

}  