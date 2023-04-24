#pragma once

#include "Enemy.h"
#include "Entity.h"
#include "Mario.h"
#include <QObject>
#include "QTimer.h"
#include "Canon.h"
#include "Testo.h"
#pragma once

class Turtle : public Enemy
{
	Q_OBJECT

protected:

	// textures
	QPixmap texture_fly_sx[2];
	QPixmap texture_fly_dx[2];
	QPixmap texture_walk_sx[2];// walking animation (2 textures)
	QPixmap texture_walk_dx[2];
	QPixmap texture_predead;
	QPixmap texture_dead;
	QGraphicsTextItem* text;


	// animation divisors (inversely proportional to animation speed)
	static const int walk_div = 20;			// walking animation

public:

	Turtle(QPoint position, Direction direction);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "Turtle"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir);
	virtual void fly();
	int help_die = 0;
	QTimer textT;


	// hurt
	virtual void hurt();

public slots:

	void collidemario();
	void settext();
};
