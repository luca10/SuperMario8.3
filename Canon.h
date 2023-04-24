#pragma once

#include "Enemy.h"
#include "Mario.h"
#include <QObject>
#include "QTimer.h"
#include "Testo.h"

//class Canon : public Enemy
class BulletBill : public Enemy{
 Q_OBJECT

protected:

	// textures
	QPixmap texture_walk[2];					// walking animation (2 textures)
	QPixmap texture_dead;
	QPoint spawned_position;
	
	// animation divisors (inversely proportional to animation speed)
	static const int walk_div = 10;			// walking animation
	
public:

	BulletBill(QPoint position,int type,Direction dir);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "Canon"; }
	float contatore = 0;
	QGraphicsTextItem* text;
	
	QTimer collideM, textT, Die;
	virtual void hit(Object *what, Direction fromDir);

	// hurt
	virtual void hurt();

	virtual void animate() {};

public slots:
	void collidemario();
	void settext();
};
