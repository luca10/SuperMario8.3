#include "Pole.h"
#include "Testo.h" 
#include <QBrush>
#include "Object.h"
#include <QPainter>
#include "Mario.h"
#include <QSound>
#include <QDebug>
#include "Game.h"

Pole::Pole(QPoint position) : Inert()
{
	setShapeMode(QGraphicsPixmapItem::MaskShape);

	// set flags
	hitted = false;
	hit_counter = 0;
	hit_duration = 16*9;
	ended = false;

	// create collage texture
	QPixmap collage(loadTexture(":/graphics/end-line.bmp"));
	collage = collage.scaled(16, 10*16);
	QPainter painter(&collage);
	QPixmap single_block(loadTexture(":/graphics/end-line.bmp"));
	Game::instance()->tes = new QGraphicsTextItem();
	for(int y=0; y<160; y += single_block.height())
		painter.drawPixmap(0, y, single_block);
	setPixmap(collage);

	// create end pole and flag
	endpole = new Background(position - QPoint(0,10*16), ":/graphics/end-dot.bmp");
	flag = new Background(position - QPoint(8,9*16), ":/graphics/end-flag.bmp");

	// set a high z-value so it is displayed on top of other objects
	setZValue(0);

	// set position
	setPos(position - QPoint(0,10*16));
}

void Pole::advance()
{
	
	if(hitted)
	{
		hit_counter++;
		if(hit_counter < hit_duration)
			flag->setY(flag->y()+1);
		else
		{
			hit_counter = 0;
			hitted = false;
			ended = true;
			
			Game::instance()->getMario()->endSlide();
		}
		
	}
}

void Pole::hit(Object *what, Direction fromDir)
{
	if(ended)
		return;

	Mario *mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		// stop level music
		Game::instance()->stopMusic();
		Game::instance()->tes->setPlainText(QString("5000"));
		Game::instance()->tes->setDefaultTextColor(Qt::white);
		Game::instance()->tes->setFont(QFont("Super Mario 256", 3));
		Game::instance()->tes->setPos(this->x()+5, this->y() +150);
		Game::instance()->tes->setFlag(QGraphicsTextItem::ItemIsMovable, true);
		

		text = Game::instance()->tes;

		Game::instance()->getScene()->addItem(text);
		textT.start();
		QObject::connect(&textT, SIGNAL(timeout()), this, SLOT(settext()));
		textT.setInterval(10);
		Testo::instance()->update_points(5000);
		// start flag animation
		hitted = true;
		Testo::instance()->time.stop();
		collidable = false;
		Testo::instance()->cpoint;
		//mario->setFreezed(true);
		mario->startSlide();
		
		// play level end music
		QSound::play(":/sounds/levelend.wav");

	}
}
void Pole::settext()
{
	text->moveBy(0,-2);
	textT.setInterval(30);
	textTimeCounter += 30;

	
	if (textTimeCounter >= 2300) // if 3 seconds have passed
	{
		textT.stop(); // stop the timer		
		delete text;
		end_level.start();
		QObject::connect(&end_level, SIGNAL(timeout()), this, SLOT(end()));
		end_level.setInterval(10);
	}

}
void Pole::end()
{
	textTimeCounter1 += 50;
	textTimeCounter2 += 20;

	if (textTimeCounter1 >= 1600)
	{
		Game::instance()->getMario()->setVisible(false);
	}
	if (textTimeCounter2 >= 12000)
	{
		Game::instance()->goreset();
		Testo::instance()->getScene()->setBackgroundBrush(Qt::black);
	}
		
		
}
