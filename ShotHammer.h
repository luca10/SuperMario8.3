#pragma once

#include "Enemy.h"
#include "Mario.h"
#include "Hammer.h"
#include <QObject>
#include "QTimer.h"

//class Canon : public Enemy
class ShotHammer : public Enemy {
	Q_OBJECT

protected:

	// textures
	QPixmap texture_walk[5];					// walking animation (2 textures)
	QPixmap texture_walk2[5];					// walking animation (2 textures)
	QPixmap texture_dead;
	QPoint spawned_position;

	// animation divisors (inversely proportional to animation speed)
	static const int walk_div = 10;			// walking animation

public:

	ShotHammer(QPoint position,Direction dir);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "ShotHammer"; }
	float contatore = 0;

	QTimer startShot, collideM;
	virtual void hit(Object *what, Direction fromDir);

	// hurt
	virtual void hurt();

	virtual void animate();

public slots:

	void startshot();
	void collidemario();

};
