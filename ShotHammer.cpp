#include "ShotHammer.h"
#include "Mario.h"
#include "Game.h"
#include "Object.h"
#include "Terrain.h"
#include "Hammer.h"
#include <QSound>
#include <QDebug>

ShotHammer::ShotHammer(QPoint position, Direction dir)
{
	// set textures
	texture_walk[0] = QPixmap(loadTexture(":/graphics/World8.3/hammer_0.bmp"));
	texture_walk[1] = QPixmap(loadTexture(":/graphics/World8.3/hammer_1.bmp"));
	texture_walk[2] = QPixmap(loadTexture(":/graphics/World8.3/hammer_2.bmp"));
	texture_walk[3] = QPixmap(loadTexture(":/graphics/World8.3/hammer_3.bmp"));

	texture_walk2[0] = QPixmap(loadTexture(":/graphics/World8.3/hammer_0.bmp"));
	texture_walk2[1] = QPixmap(loadTexture(":/graphics/World8.3/hammer_1.bmp"));
	texture_walk2[2] = QPixmap(loadTexture(":/graphics/World8.3/hammer_2.bmp"));
	texture_walk2[3] = QPixmap(loadTexture(":/graphics/World8.3/hammer_3.bmp"));
	collidable = false;
	falling = false;
	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, 6));
	moving_speed = 2;
	jumping_speed = 10;
	moving_speed_div = 1;

	
	setZValue(3);

	collideM.start();
	QObject::connect(&collideM, SIGNAL(timeout()), this, SLOT(collidemario()));
	collideM.setInterval(10);

	if(Game::instance()->getMario()->pos().x() < pos().x())
		setDirection(LEFT);
	else
		setDirection(RIGHT);

	
	startShot.start();
	QObject::connect(&startShot, SIGNAL(timeout()), this, SLOT(startshot()));
	startShot.setInterval(200);	
	Game::instance()->getHammer()->shots = true;
}
void ShotHammer::startshot() {

	falling = true;

}
void ShotHammer::animate()
{
		setPixmap(texture_walk[(walk_counter++ / walk_div) % 4]);
}
void ShotHammer::hit(Object *what, Direction fromDir)
{
	setDirection(dir);
}
void ShotHammer::collidemario()
{
	if (sceneBoundingRect().intersects(Game::instance()->getMario()->sceneBoundingRect()))
		collidable = true;
}
// hurt
void ShotHammer::hurt()
{
	//QSound::play(":/sounds/stomp.wav");
	//die();
}
