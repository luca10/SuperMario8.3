#include "Box.h"
#include "Mario.h"
#include "CoinSpawnable.h"
#include "Game.h"
#include "Testo.h" 
#include "Mushroom.h"
#include "Flower.h"
#include "Object.h"
#include <QSound>
#include <QDebug>
#include <QObject>

Box::Box(QPoint position, visibility_t _visibility, spawnable_t _spawnable) : Inert()
{
	// load textures
	texture_cycle[0] = loadTexture(":/graphics/box-0.bmp");
	texture_cycle[1] = loadTexture(":/graphics/box-1.bmp");
	texture_cycle[2] = loadTexture(":/graphics/box-2.bmp");
	texture_used = loadTexture(":/graphics/World8.3/box-used.bmp");
	texture_brick = loadTexture(":/graphics/World8.3/brick.bmp");

	Game::instance()->tes = new QGraphicsTextItem();
	text = new QGraphicsTextItem();
	// set properties
	used = false;
	hitted = false;
	hit_counter = 0;
	visibility = _visibility;
	spawnable = _spawnable;
	if (visibility == INVISIBLE)
		this->setOpacity(0.0);

	// set texture and position
	setPixmap(texture_cycle[0]);
	setPos(position);

	// be sure z-value is above mushroom's one
	setZValue(3);

}

void Box::animate()
{
	if (used)
		setPixmap(texture_used);
	else if (visibility == BRICKED)
		setPixmap(texture_brick);
	else
		setPixmap(texture_cycle[(hit_counter++ / anim_div) % 3]);
}

void Box::advance()
{
	// hit by Mario: move upwards and downwards
	if (hitted)
	{
		//visibility = VISIBLE;
		//setOpacity(1.0);

		if (hit_counter < 10)
			setY(y() - 1);
		else if (hit_counter < 20)
			setY(y() + 1);

		/*if (hit_counter > 20)
			hitted = false;
			*/
		hit_counter++;
	}
}

void Box::hit(Object *what, Direction fromDir)
{
	// hit by Mario from bottom
	if (dynamic_cast<Testo*>(what))
		collidable = false;

	Mario* mario = dynamic_cast<Mario*>(what);		
	if (mario && fromDir == DOWN)
	{
		if (used) {
			QSound::play(":/sounds/block-hit.wav");
		}
		else
		{
			// spawn object
			if (spawnable == COIN && tcoin < 6)
			{
				new CoinSpawnable(QPoint(x(), y() - 20));
				tcoin++;
				Game::instance()->tes = new QGraphicsTextItem();
				Game::instance()->tes->setPlainText(QString("200"));
				Game::instance()->tes->setDefaultTextColor(Qt::white);
				Game::instance()->tes->setFont(QFont("Super Mario 256", 3));
				Game::instance()->tes->setPos(this->x(), this->y() - 16);
				Game::instance()->tes->setFlag(QGraphicsTextItem::ItemIsMovable, true);
				
				text = Game::instance()->tes;
			
				Game::instance()->getScene()->addItem(text);
				Ttext.start();
				QObject::connect(&Ttext, SIGNAL(timeout()), this, SLOT(settext()));
				Ttext.setInterval(200);


				Testo::instance()->update_points(200);
				Testo::instance()->update_coin(1);			
			}
			else if (spawnable == POWERUP)
			{
				if (mario->isBig() || mario->isFire())
					new Flower(QPoint(x(), y()));
				else
					new Mushroom(QPoint(x(), y()));
			}
			else if (spawnable == LIFE)
				new Mushroom(QPoint(x(), y()), false);

			hitted = true;
			hit_counter = 0;

			// set flags / counters
			if (tcoin==6 || spawnable == POWERUP || spawnable == LIFE)
			{		
				used = true;			
				setPixmap(texture_used);
				tcoin = 0;
			}
		
		}
	}
}
void Box::settext()
{

	text->moveBy(0, -4);

		delete text;
		text = new QGraphicsTextItem();


}
