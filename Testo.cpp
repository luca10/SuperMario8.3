#include "Testo.h"
#include "Enemy.h"
#include "Game.h"
#include "Object.h"
#include "Mario.h"
#include "Canon.h"
#include "CoinSpawnable.h"
#include <QSound>
#include <QLabel>
#include <QPainter>
#include <QBrush>
#include <QtWidgets>
#include <QGraphicsPixmapItem>

Testo* Testo::uniqueInstance = nullptr;
Testo* Testo::instance(QWidget* parent)
{
	if (uniqueInstance == nullptr)
		uniqueInstance = new Testo(parent);
	return uniqueInstance;
}
Testo::Testo(QWidget* parent) : QGraphicsView(parent)
{
	
	scene = new QGraphicsScene();
	scene->setBackgroundBrush(QColor(99, 133, 251));
	setScene(scene);
	
	setFixedSize(928, 68);
	
	scale(2.0, 2.0);
	
	scene->setSceneRect(0, 0, 896, 48);

	setFrameShape(QFrame::NoFrame);
	setInteractive(false);		// disables events
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	texture_cycle[0] = QPixmap(loadTextureTransparent(":/graphics/coin-0.png"));
	texture_cycle[1] = QPixmap(loadTextureTransparent(":/graphics/coin-1.png"));
	texture_cycle[2] = QPixmap(loadTextureTransparent(":/graphics/coin-2.png"));
	texture_cycle[3] = QPixmap(loadTextureTransparent(":/graphics/coin-3.png"));
	
	
	test01 = new QGraphicsPixmapItem();

	walk = 0;
	

	time_ui = new QGraphicsTextItem();
	point = new QGraphicsTextItem();
	Ccoin = new QGraphicsTextItem();
	
	QObject::connect(&time, SIGNAL(timeout()), this, SLOT(update_ui()));
	time.setInterval(1000);
	
		
}
void Testo::update_ui()
{
	
	 time_ui->setPlainText(QString::number(ctime--));
	 test01->setPixmap(texture_cycle[walk]);
	 walk++;
	 if (walk == 3)
		 walk = 0;
	 if (ctime < 0)
		 Game::instance()->getMario()->die();
	 if (ctime < 150 && mus == 0)
	 {
		 Game::instance()->music->stop();
		 Game::instance()->music = new QSound(":/sounds/overworld-fast.wav");
		 Game::instance()->music->setLoops(QSound::Infinite);
		 Game::instance()->music->play();
		mus = 1;
	}

	 //}
}
void Testo::add_end()
{
	help_point = cpoint;
	help_point1 = ctime;
	fine.start();
	QObject::connect(&fine, SIGNAL(timeout()), this, SLOT(set_end_point()));
	fine.setInterval(10);
	music = new QSound(":/sounds/coin.wav");
	music->setLoops(QSound::Infinite);
	
	
}
void Testo::set_end_point()
{
	
	/*if (help_point >= 10) {	
		help_point = help_point - 10;
		help_point1 = help_point1 + 10;
		time_ui->setPlainText(QString::number(help_point1));
		point->setPlainText(QString::number(help_point));
		music->play();
	}
	else
		music->stop();*/
	if (help_point1 >= 1) {
		help_point1 = help_point1 - 1;
		help_point = help_point + 50;
		time_ui->setPlainText(QString::number(help_point1));
		point->setPlainText(QString::number(help_point));
		music->play();
	}
	else
		music->stop();
}
void Testo::update_points(int points)
{
	cpoint += points;

	point->setPlainText(QString::number(cpoint));
	
}
void Testo::update_coin(int coins)
{
	coin += coins;

	Ccoin->setPlainText(QString::number(coin));

}
void Testo::start()
{
	time.start();
	ctime = 300;
	QGraphicsTextItem* test;
	test = new QGraphicsTextItem();
	test->setPlainText(QString("MARIO"));
	test->setDefaultTextColor(Qt::white);
	test->setFont(QFont("Super Mario 256", 10));
	test->setPos(16, 0); 
	test->setFlag(QGraphicsTextItem::ItemIsMovable, true);
	
	instance()->getScene()->addItem(test);

	cpoint = 0;
	point->setPlainText(QString::number(cpoint));
	point->setDefaultTextColor(Qt::white);
	point->setFont(QFont("Super Mario 256", 10));
	point->setPos(2 * 16, 14);
	point->setFlag(QGraphicsTextItem::ItemIsMovable, true);
	instance()->getScene()->addItem(point);

	
	test01->setPixmap(texture_cycle[0]);
	test01->setPos(8 * 16, 14);

	instance()->getScene()->addItem(test01);
	
	/*textcoin = loadTexture(":/graphics/coin-0.png");
	textcoin[1] = loadTexture(":/graphics/coin-1.png");
	textcoin[2] = loadTexture(":/graphics/coin-2.png");
	textcoin[3] = loadTexture(":/graphics/coin-3.png");
	test01 = new QGraphicsPixmapItem();
	test01->setPixmap(textcoin);
	test01->setPos(8 * 16, 14);*/
	
	//instance()->getScene()->addItem(test01);

	QGraphicsTextItem* test1;
	test1 = new QGraphicsTextItem();
	test1->setPlainText(QString("x"));
	test1->setDefaultTextColor(Qt::white);
	test1->setFont(QFont("Super Mario 256", 8));
	test1->setPos(9*16, 14);
	test1->setFlag(QGraphicsTextItem::ItemIsMovable, true);

	instance()->getScene()->addItem(test1);

	coin = 0;
	Ccoin->setPlainText(QString::number(coin));
	Ccoin->setDefaultTextColor(Qt::white);
	Ccoin->setFont(QFont("Super Mario 256", 10));
	Ccoin->setPos( 11* 16, 14);
	Ccoin->setFlag(QGraphicsTextItem::ItemIsMovable, true);
	instance()->getScene()->addItem(Ccoin);


	QGraphicsTextItem* test2;
	test2 = new QGraphicsTextItem();
	test2->setPlainText(QString("WORLD"));
	test2->setDefaultTextColor(Qt::white);
	test2->setFont(QFont("Super Mario 256", 10));
	test2->setPos(16 * 16, 0);
	test2->setFlag(QGraphicsTextItem::ItemIsMovable, true);

	instance()->getScene()->addItem(test2);

	QGraphicsTextItem* test3;
	test3 = new QGraphicsTextItem();
	test3->setPlainText(QString("8-3"));
	test3->setDefaultTextColor(Qt::white);
	test3->setFont(QFont("Super Mario 256", 10));
	test3->setPos(17 * 16, 14);
	test3->setFlag(QGraphicsTextItem::ItemIsMovable, true);

	instance()->getScene()->addItem(test3);

	QGraphicsTextItem* test4;
	test4 = new QGraphicsTextItem();
	test4->setPlainText(QString("Time"));
	test4->setDefaultTextColor(Qt::white);
	test4->setFont(QFont("Super Mario 256", 10));
	test4->setPos(23 * 16, 0);
	test4->setFlag(QGraphicsTextItem::ItemIsMovable, true);

	instance()->getScene()->addItem(test4);

	//QGraphicsTextItem* test5;
	//test5 = new QGraphicsTextItem();
	time_ui->setPlainText(QString::number(ctime));
	time_ui->setDefaultTextColor(Qt::white);
	time_ui->setFont(QFont("Super Mario 256", 10));
	time_ui->setPos(23.5 *  16, 14);
	time_ui->setFlag(QGraphicsTextItem::ItemIsMovable, true);

	instance()->getScene()->addItem(time_ui);

}
