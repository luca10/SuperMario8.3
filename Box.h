#pragma once

#include "Inert.h"
#include "Mario.h"
#include <QObject>
#include "QTimer.h"
#include "Testo.h"
// spawnable objects
enum spawnable_t {
	COIN,			// coin
	POWERUP,		// powerup for Mario (Red Mushroom or Flower) 
	LIFE,			// life up for Mario (Green Mushroom)
	VINE
};			// vine

enum visibility_t {
	VISIBLE,		// fully visible
	BRICKED,		// hidden by a brick block
	INVISIBLE		// invisible
};

class Box : public Inert
{
	Q_OBJECT
protected:

	// textures
	QPixmap texture_cycle[3];		// animation cycle
	QPixmap texture_used;			// texture for 'used' state
	QPixmap texture_brick;			// texture for 'bricked' state

	// flags
	bool used;						// whether the box has been used
	bool hitted;					// whether the box has been hit by Mario

	// properties
	visibility_t visibility;		// visibility
	spawnable_t spawnable;			// spawnable object

	// animation divisors (inversely proportional to animation speed)
	static const int anim_div = 40;	// main animation

	// counters
	int  hit_counter;				// counts the number of frames since Mario hit
	int tcoin = 0;
	QGraphicsTextItem* text;

public:

	Box(QPoint position, visibility_t _visibility = VISIBLE, spawnable_t _spawnable = COIN);

	QTimer Ttext;
	int textTimeCounter = 0;
	// getters
	visibility_t getVisibility() { return visibility; }

	// inherited methods
	virtual std::string name() { return "Box"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object *what, Direction fromDir);

public slots:

	void settext();
};