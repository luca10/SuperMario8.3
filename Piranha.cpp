#include "Turtle.h"
#include "Mario.h"
#include "Entity.h"
#include <QSound>
#include "Game.h"
#include "Object.h"
#include "Canon.h"
#include "Terrain.h"
#include "Piranha.h"
#include <QSound>
#include <QDebug>

Piranha::Piranha(QPoint position, Direction direction)
{
	// set textures
	texture_walk[0] = QPixmap(loadTexture(":/graphics/World8.3/piranha-0.png"));
	texture_walk[1] = QPixmap(loadTexture(":/graphics/World8.3/piranha-1.png"));

	// set direction
	dir = direction;
	//setZValue(2);
	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, pixmap().height()));
	dir = UP;

	falling = true;
	jumping = true;
	collidable = false;
	moving_speed = 1;
	jumping_speed = 1;
	falling_speed = 1;
	moving_speed_div = 1;
	jumping_duration = 16;


	collide.start();
	QObject::connect(&collide, SIGNAL(timeout()), this, SLOT(collidemario()));
	collide.setInterval(1);

	piranhaUp.start();
	QObject::connect(&piranhaUp, SIGNAL(timeout()), this, SLOT(Up()));
	piranhaUp.setInterval(2000);

}

void Piranha::animate()
{
	if (moving)
	{
		setPixmap(texture_walk[(walk_counter++ / walk_div) % 2]);
	}
}
void Piranha::Up()
{
	dir = DOWN;
	if (moving)
	{
		setPixmap(texture_walk[(walk_counter++ / walk_div) % 2]);
	}
	die();

}
void Piranha::collidemario()
{
	if (sceneBoundingRect().intersects(Game::instance()->getMario()->sceneBoundingRect()))
		collidable = true;
}
void Piranha::hit(Object *what, Direction fromDir)
{
	collidemario();
}
// hurt
void Piranha::hurt()
{

}

