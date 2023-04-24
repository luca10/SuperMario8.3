#include "Canon.h"
#include "Mario.h"
#include "Game.h" 
#include "Testo.h" 
#include "Object.h"
#include "Terrain.h"
#include <QSound>
#include <QDebug>

BulletBill::BulletBill(QPoint position,  int type,Direction dir)
{
	// set textures
	texture_walk[0] = QPixmap(loadTexture(":/graphics/World8.3/bulletbill.bmp"));
	texture_walk[1] = QPixmap(loadTexture(":/graphics/World8.3/bulletbill1.bmp"));
	// set direction
	collideM.start();
	// set texture and correct y-coordinate w.r.t. texture height
	setZValue(2);
	collidable = false;
	falling = false;
	Game::instance()->tes = new QGraphicsTextItem();
	if (type == 1)
	{
		QSound::play(":/sounds/bulletbill.wav");
		if(dir==LEFT)
			setPixmap(texture_walk[0]);
		else
		    setPixmap(texture_walk[1]);


			setPos(position - QPoint(32, pixmap().height() + 16));
			moving = false;
			contatore++;
	}
	if (type == 2)
	{
		QSound::play(":/sounds/bulletbill.wav");
		if (dir == LEFT)
			setPixmap(texture_walk[0]);
		else
		    setPixmap(texture_walk[1]);

			setPos(position - QPoint(16, pixmap().height() + 32));
			moving = false;
	}

	
	QObject::connect(&collideM, SIGNAL(timeout()), this, SLOT(collidemario()));
	collideM.setInterval(1);


}
void BulletBill::collidemario() {

	if (sceneBoundingRect().intersects(Game::instance()->getMario()->sceneBoundingRect()))
		collidable = true;
	else
		collidable = false;
}
void BulletBill::hit(Object *what, Direction fromDir)
{
	setDirection(dir);
}

// hurt
void BulletBill::hurt()
{
	QSound::play(":/sounds/stomp.wav");
	Game::instance()->tes = new QGraphicsTextItem();
	Game::instance()->tes->setPlainText(QString("200"));
	Game::instance()->tes->setDefaultTextColor(Qt::white);
	Game::instance()->tes->setFont(QFont("Super Mario 256", 3));
	Game::instance()->tes->setPos(this->x(), this->y()-16);
	Game::instance()->tes->setFlag(QGraphicsTextItem::ItemIsMovable, true);
	text = Game::instance()->tes;

	Game::instance()->getScene()->addItem(text);

	textT.start();
	QObject::connect(&textT, SIGNAL(timeout()), this, SLOT(settext()));
	textT.setInterval(200);
	collideM.stop();
	Testo::instance()->update_points(200);
	
	if(dir==LEFT)
		setPixmap(texture_walk[1]);
	else
		setPixmap(texture_walk[0]);


	falling = false;
	collidable = false;
	dying = true;
	dir = DOWN;
}
void BulletBill::settext()
{
	die();
	textT.stop();
	delete text;

}