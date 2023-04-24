 #pragma once

#include "Entity.h"
#include "Enemy.h"
#include "Mario.h"
#include <QObject>
#include "QTimer.h"
#include "Brick.h"

//class Canon : public Enemy
class Hammer : public Enemy
{
	Q_OBJECT

protected:

	// textures
	QPixmap texture_walk[12];					// walking animation (2 textures)
	QPixmap texture_walk2[10];					// walking animation (2 textures)
	QPixmap texture_shot[20];			// walking animation (2 textures)
	QPixmap texture_dead;
	QPixmap texture_throw[6];
	QPoint spawned_position;
	QGraphicsTextItem* points;

	// animation divisors (inversely proportional to animation speed)
	static const int walk_div = 20;			// walking animation
	
	int salto = 0;
public:

	Hammer(QPoint position, Direction dir);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "Hammer"; }
	
	QTimer setactions, inver_dir, nshot,Ttext, shotted;
	int conta_salto = 0;
	int action=0;
	bool shots;
	virtual void hit(Object* what, Direction fromDir);
	virtual void hurt();
	virtual void animate();
	virtual void die();
	void setCollidable();
	

public slots:

	void settext();
	void jump();
	void shot();
	void actions();
	void help_dir();
	void death() { death_duration++; }
	void set_shot();
	
};
