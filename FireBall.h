#pragma once

#include "Entity.h"
#include <QObject>
#include<QDebug>

class FireBall : public Entity
{

protected:

	QPixmap texture_walk[4];					
	QPixmap texture_end;
	QPoint spawned_position;
	static const int walk_div = 10;


public:

	FireBall(QPoint position, Direction dir);

	virtual void die();
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual std::string name() { return "FireBall"; }
};