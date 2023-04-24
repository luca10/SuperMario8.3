#include "Canon.h"
#include "Mario.h"
#include "Game.h"
#include "Object.h"
#include "Terrain.h"
#include <QSound>
#include "Hammer.h"
#include <QDebug>
#include "Brick.h"
#include "ShotHammer.h"
#include "Brick.h"
#include "Fireball.h"
#include "Turtle.h"
#include "Testo.h"

Hammer::Hammer(QPoint position, Direction dir)
{
	// set textures
	texture_dead = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_die.bmp"));

	texture_walk[0] = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_0.bmp"));
	texture_walk[1] = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_1.bmp"));
	

	texture_shot[0] = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_2.bmp"));
	texture_shot[1] = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_3.bmp"));

	texture_walk2[0] = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_01.bmp"));
	texture_walk2[1] = QPixmap(loadTextureTransparent(":/graphics/World8.3/hammerbro_11.bmp"));

	setPixmap(texture_walk[0]);
	setPos(position - QPoint(32, pixmap().height()));
	setZValue(3);
	Game::instance()->tes = new QGraphicsTextItem();
	setDirection(dir);

	collidable = true;
	//falling = true;
	//jumping = true;
	moving_speed = 1;
	jumping_speed = 1;
	falling_speed = 1;
	moving_speed_div = 32;

	//funzione per saltare in modo random
	int ritardo = rand() % 1500 + 2500;
	setactions.start();
	QObject::connect(&setactions, SIGNAL(timeout()), this, SLOT(actions()));
	setactions.setInterval(ritardo + ritardo);
	//funzione per invertire la direzione
	inver_dir.start();
	QObject::connect(&inver_dir, SIGNAL(timeout()), this, SLOT(help_dir()));
	inver_dir.setInterval(2700);
	shots = false;
	//funzione per lo shot
	nshot.start();
	QObject::connect(&nshot, SIGNAL(timeout()), this, SLOT(shot()));
	nshot.setInterval(2400);
}
void Hammer::help_dir()
{
	if (dir == RIGHT || dir == LEFT)
		setDirection(inverse(dir));
}
void Hammer::animate()
{
	if (jumping)
		collidable = false;
	else
		if (falling && action == 2 && pos().y() == 184 && salto>0) {

			salto = 0;
			collidable = true; 		
		}else if(falling && action == 2)
		{
			salto++;
			collidable = false;
		}
		else
			collidable = true;

	if (pos().y() == 280 - 32)
		collidable = true;	

	
	if(Game::instance()->getMario()->pos().x() < pos().x())
		if (shots) {
			setPixmap(texture_shot[(walk_counter++ / walk_div) % 2]);
			
		}
		else
			setPixmap(texture_walk[(walk_counter++ / walk_div) % 2]);
	else
			setPixmap(texture_walk2[(walk_counter++ / walk_div) % 2]);


	if (dying || dead) {
		setPixmap(texture_dead);
		collidable = false;
	}
	
}

void Hammer::shot()
{
	shots = true;
		new ShotHammer(QPoint(pos().x(), pos().y()), dir);
		shotted.start();
		QObject::connect(&shotted, SIGNAL(timeout()), this, SLOT(set_shot()));
		shotted.setInterval(20);
}
void Hammer::set_shot()
{
	shots = false;
		shotted.stop();
}
void Hammer::jump()
{
	if (!falling && !jumping)
	{
		collidable = false;
		walkable_object = 0;
		jumping = true;
		moving_speed = 1;
		jumping_speed = 1;
		falling_speed = 1;
		moving_speed_div = 16;
		jumping_duration = 80;
		falling = false;

	}

}

void Hammer::actions()
{
	
	action = rand() % 2 + 1;
	
	if (!jumping && !falling)
	{
		if (action == 1 && conta_salto <= 2)
		{
			
			jumping_duration = 80;
			startJumping();
			conta_salto++;
		}

		if (action == 2 && pos().y() != 280 && conta_salto>=1)
		{
		
			falling = true;
			conta_salto--;
		}
	}

}
void Hammer::die()
{	
	dying = true;	
	
	//HammerBro start falling afer he dies
	collidable = false;
	falling = true;
	// make a slow jmp
	jumping_speed = 2;
	falling_speed = 2;
	dir = DOWN;
	setactions.stop();
}

void Hammer::setCollidable() {
	collidable = true;
}

void Hammer::hurt()
{
	//viene aggiunto il punteggio 
	Game::instance()->tes = new QGraphicsTextItem();
	Game::instance()->tes->setPlainText(QString("200"));

	Game::instance()->tes->setDefaultTextColor(Qt::white);
	Game::instance()->tes->setFont(QFont("Super Mario 256", 3));
	Game::instance()->tes->setPos(this->x(), this->y() - 16);
	Game::instance()->tes->setFlag(QGraphicsTextItem::ItemIsMovable, true);
	points = Game::instance()->tes;

	Game::instance()->getScene()->addItem(points);

	Ttext.start();
	QObject::connect(&Ttext, SIGNAL(timeout()), this, SLOT(settext()));
	Ttext.setInterval(500);

	Testo::instance()->update_points(200);
	die();
}

void Hammer::hit(Object* what, Direction fromDir) {
	//cast con le palle infuocate
	if (dynamic_cast<FireBall*>(what))
		hurt();
	//cast con tartatuga
	if (dynamic_cast<Turtle*>(what))
	{
		collidable = false;
		hurt();
	}
	Brick* brick_obj = dynamic_cast<Brick*>(what);
	
	if (brick_obj) {


		QRectF brick = brick_obj->sceneBoundingRect();
	
		QRectF curr_rect = sceneBoundingRect();
		
		QRectF interRect = curr_rect.intersected(brick);
		
		//Solve Collisions between HammerBro and Brick 
		if (interRect.bottom() - 2 == brick.y()) {
			hurt();
		}
	

		if (brick_obj->isBroken()) {

			hurt();
			brick_obj->HammerDead = true;

		}
	}
}
void Hammer::settext()
{
	Ttext.stop();
	delete points;

}