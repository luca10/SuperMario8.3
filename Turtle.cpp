#include "Turtle.h"
#include "Mario.h"
#include "Entity.h"
#include <QSound>
#include "Game.h"
#include "Object.h"
#include "Canon.h"
#include "Terrain.h"
#include "Testo.h"
#include "FireBall.h"
#include <QSound>
#include <QDebug>

Turtle::Turtle(QPoint position, Direction direction) 
{
	// set textures
	texture_fly_sx[0] = QPixmap(loadTexture(":/graphics/World8.3/turtle-fly-0.png"));
	texture_fly_sx[1] = QPixmap(loadTexture(":/graphics/World8.3/turtle-fly-1.png"));

	texture_fly_dx[0] = QPixmap(loadTexture(":/graphics/World8.3/turtle-fly-00.png"));
	texture_fly_dx[1] = QPixmap(loadTexture(":/graphics/World8.3/turtle-fly-11.png"));

	texture_walk_sx[0] = QPixmap(loadTexture(":/graphics/World8.3/turtle-walk-0.png"));
	texture_walk_sx[1] = QPixmap(loadTexture(":/graphics/World8.3/turtle-walk-1.png"));

	texture_walk_dx[0] = QPixmap(loadTexture(":/graphics/World8.3/turtle-walk-00.png"));
	texture_walk_dx[1] = QPixmap(loadTexture(":/graphics/World8.3/turtle-walk-11.png"));
	
	Game::instance()->tes = new QGraphicsTextItem();
	text = new QGraphicsTextItem();
	texture_dead = QPixmap(loadTexture(":/graphics/World8.3/turtle-turtleback-0.png"));

	falling = true;
	jumping = true;
	//collidable = false;
	// set direction
	dir = direction;

	// set texture and corre\	ct y-coordinate w.r.t. texture height
	setPixmap(texture_fly_sx[0]);
	setPos(position - QPoint(0, pixmap().height()));

	help_die = 1;
}
void Turtle::animate()
{
	if (dir == LEFT )
	{
		if (moving)
		{
			if (help_die == 1) {
				fly();
				setPixmap(texture_fly_sx[(walk_counter++ / walk_div) % 2]);
				
			}

			if(help_die == 2)
			{
				setPixmap(texture_walk_sx[(walk_counter++ / walk_div) % 2]);
			}
		}
		if(help_die ==3)
			setPixmap(texture_dead);

	}
	if (dir == RIGHT )
	{
		if (help_die == 1)
			fly();

		 if (moving)
		{

			 if (help_die == 1) {
				 fly();
				 setPixmap(texture_fly_dx[(walk_counter++ / walk_div) % 2]);
			 }
				if (help_die == 2)
					setPixmap(texture_walk_dx[(walk_counter++ / walk_div) % 2]);

		}
		if (help_die == 3)
			 setPixmap(texture_dead);

	}

}

void Turtle::hit(Object *what, Direction fromDir)
{
	if (dynamic_cast<FireBall*>(what))
		die();

	if (dynamic_cast<Hammer*>(what))
		setDirection(inverse(dir));

	if (dynamic_cast<Mario*>(what))
		setDirection((dir));

	
	if (fromDir == RIGHT || fromDir == LEFT)
	{
		setDirection(inverse(dir));	
	}

}

// hurt
void Turtle::hurt()
{
	if (help_die <= 2) {
		Game::instance()->tes = new QGraphicsTextItem();
		Game::instance()->tes->setPlainText(QString("100"));
		Game::instance()->tes->setDefaultTextColor(Qt::white);
		Game::instance()->tes->setFont(QFont("Super Mario 256", 3));
		Game::instance()->tes->setPos(this->x(), this->y() - 16);
		Game::instance()->tes->setFlag(QGraphicsTextItem::ItemIsMovable, true);
		text = Game::instance()->tes;

		Game::instance()->getScene()->addItem(text);

		textT.start();
		QObject::connect(&textT, SIGNAL(timeout()), this, SLOT(settext()));
		textT.setInterval(200);
		

		Testo::instance()->update_points(100);
	}
	if (help_die == 1)
	{
		jumping_speed = 0;
		falling = true;
		help_die = 2;
		moving_speed_div = 4;
		

	}
	else if (help_die == 2)
	{
		help_die = 3;
		moving_speed_div = 1;
		moving_speed = 4;
		setDirection(RIGHT);
	
	}
	else if (help_die == 3 && moving)
		moving = false;
	else
		moving = true;
	
}

void Turtle::settext()
{
	text->moveBy(0, -4);
	delete text;
	text= new  QGraphicsTextItem();
}

void Turtle::fly()
{
	if (!falling && !jumping)
	{
		walkable_object = 0;
		jumping = true;
		moving_speed = 1;
		jumping_speed = 1;
		falling_speed = 1;
		moving_speed_div = 8;
		jumping_duration = 28;
	}

}
void Turtle::collidemario() {


	if (sceneBoundingRect().intersects(Game::instance()->getMario()->sceneBoundingRect()))
		collidable = true;
}
