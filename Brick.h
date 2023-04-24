#pragma once

#include "Inert.h"
#include <QObject>
#include "QTimer.h"
#include "Hammer.h"
class Brick : public Inert
{

	Q_OBJECT
protected:

	bool hitted, hitted_big;				// whether the brick has been hit by Mario
	bool broken;				// whether the brick has been broken by Mario
	int  broke, hit_counter;			// counts the number of frames since Mario hit

public:

	Brick(QPoint position);

	// inherited methods
	virtual std::string name() { return "Brick"; }
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);

	bool isBroken() { return hitted_big; }
	bool HammerDead;

public slots:
	void setjump();

};