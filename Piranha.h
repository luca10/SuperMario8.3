#pragma once

#include "Enemy.h"
#include "Entity.h"
#include "Mario.h"
#include <QObject>
#include "QTimer.h"
#include "Canon.h"
#pragma once

class Piranha: public Enemy
{
	Q_OBJECT

protected:

	// textures
	QPixmap texture_walk[3];
	QPoint spawned_position;


	// animation divisors (inversely proportional to animation speed)
	static const int walk_div = 10;			// walking animation

public:

	Piranha(QPoint position, Direction direction);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "Turtle"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir);

	QTimer piranhaUp, collide ;


	// hurt
	virtual void hurt();

public  slots:
	void Up();
	void collidemario();
};
