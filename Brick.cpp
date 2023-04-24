#include "Brick.h"	
#include <QBrush>
#include <QPainter>
#include "Brick.h"
#include "Mario.h"
#include "BrickDebris.h"
#include "Game.h"
#include "Hammer.h"
#include "Enemy.h"
#include <QDebug>


Brick::Brick(QPoint position) : Inert()
{
	// set texture and position
	setPixmap(QPixmap(loadTexture(":/graphics/World8.3/brick.bmp")));
	setPos(position);

	broke = 0;
	HammerDead = false;
	hitted = false;
	hitted_big = false;
	broken = false;
	hit_counter = 0;
}
void Brick::setjump()
{

	if (collidable == false)
	{
		collidable = true;

	}
}

// manage collisions with Mario
void Brick::advance()
{

	// do nothing if brick is not visible
	if (this->isVisible() == 0)
		return;

	/*if (broken && HammerDead)
	{
		setVisible(false);
		collidable = false;

	}
	else
		broke = 1;
		*/

		// hit by Mario: move upwards and downwards
	if (hitted)
	{


		if (hit_counter < 10)
		{
			setY(y() - 1);
		}
		else if (hit_counter < 20)
			setY(y() + 1);



		hit_counter++;

		/*if (hit_counter >= 20)
			{
				hitted = false;
				hit_counter = 0;
			}*/
		if (hitted_big && !broken)
		{

			//setOpacity(0);
			walkable = false;
			broken = true;

			// spawn debris
			new BrickDebris(QPoint(x(), y() - 15), LEFT);
			new BrickDebris(QPoint(x() + pixmap().width(), y() - 15), RIGHT);
			new BrickDebris(QPoint(x() - 5, y() - 5), LEFT);
			new BrickDebris(QPoint(x() + pixmap().width() + 5, y() - 5), RIGHT);

		}
		else if (broken && HammerDead)
		{
			setVisible(false);
			collidable = false;

		}
		else if (hitted_big && broken)
		{
			setVisible(false);
			collidable = false;
		}
	}
}

void Brick::hit(Object* what, Direction fromDir)
{
	// hit by Mario from bottom
	Mario* mario = dynamic_cast<Mario*>(what);

	if (mario && fromDir == DOWN)
	{
		QSound::play(":/sounds/block-hit.wav");
		hitted = true;
		hit_counter = 0;

		if (mario->isBig() || mario->isFire())
		{
			QSound::play(":/sounds/block-break.wav");
			hitted_big = true;
		}
	}
}
