#include <QApplication>
#include <QKeyEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QSound>
#include <QThread>
#include "Game.h"
#include "Object.h"
#include "LevelManager.h"
#include "Mario.h"
#include "Piranha.h"
#include "Turtle.h"
#include "Canon.h"
#include "FireBall.h"
#include <QDebug>
#include "Testo.h"
#include <QGraphicsTextItem>



// Singleton design pattern
Game* Game::uniqueInstance = nullptr;
Game* Game::instance(QWidget* parent)
{
	if (uniqueInstance == 0)
		uniqueInstance = new Game(parent);
	return uniqueInstance;
}


Game::Game(QWidget* parent) : QGraphicsView(parent)
{
	// setup scene/view
	scene = new QGraphicsScene();
	setScene(scene);
	scale(2.0, 2.0);
	centerOn(0, 0);
	setInteractive(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene->setSceneRect(0, 0, 3650, 312);
	


	QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
	engine.setInterval(10);
	mario = 0;
	
	life = 3;

	//slot per shot cannoni
	QObject::connect(&shots, SIGNAL(timeout()), this, SLOT(shot()));
	shots.setInterval(2200);

	music = new QSound(":/sounds/overworld.wav");
	music->setLoops(QSound::Infinite);
	

	//slot per piranha
	
	QObject::connect(&piranhaa, SIGNAL(timeout()),this, SLOT(piranha()));
	piranhaa.setInterval(3000);

		//slot per turtle
		QObject::connect(&turtleadd, SIGNAL(timeout()), this, SLOT(addturtle()));
		turtleadd.setInterval(500);

	// setup window size
	this->setFixedSize(928, 624);

	
	//slot per il reset
	QObject::connect(&gamer, SIGNAL(timeout()), this, SLOT(goreset()));
	gamer.setInterval(2000);

	
	reset();
}
void Game::piranha()
{
	if (cur_state != RUNNING)
		return;

	if (mario->pos().x() < (50 * 16) || mario->pos().x() > (56 * 16)) 
	{
	Piranha* shotted;


	shotted = new Piranha(QPoint(53.5 * 16, 234), DOWN);

	//getScene()->addItem(shotted);

	shotted->setMoving(true);
	shotted->setDirection(UP);
	}
	
	if (mario->pos().x() < (122 * 16) || mario->pos().x() > (131 * 16))
	{
		Piranha* shotted;


		shotted = new Piranha(QPoint(126.5 * 16, 234), DOWN);

		//getScene()->addItem(shotted);

		shotted->setMoving(true);
		shotted->setDirection(UP);
	}
	if (mario->pos().x() < (165 * 16) || mario->pos().x() > (174 * 16))
	{
		Piranha* shotted;


		shotted = new Piranha(QPoint(168.5 * 16, 250), DOWN);

		//getScene()->addItem(shotted);

		shotted->setMoving(true);
		shotted->setDirection(UP);
	}

}
void Game::addturtle()
{
	
	if (mario->pos().x() > (14 * 16) && created[0]==0)
	{
		Turtle *turtle;
		turtle = new Turtle(QPoint(33 * 16, 260), LEFT);
		//instance()->getScene()->addItem(turtle);
		turtle->setMoving(true);
		turtle->setDirection(LEFT);
		created[0] = 1;	
	}
	if (mario->pos().x() > (76 * 16) && created[1]==0)
	{

		Turtle *turtle;
		turtle = new Turtle(QPoint(93 * 16, 260), LEFT);
		//instance()->getScene()->addItem(turtle);
		turtle->setMoving(true);
		turtle->setDirection(LEFT);
		created[1] = 1;
		
	}

	if (mario->pos().x() > (123 * 16) && created[2]==0)
	{

		Turtle * turtle;
		turtle = new Turtle(QPoint(143 * 16, 200), LEFT);
		turtle->help_die = 2;
		//instance()->getScene()->addItem(turtle);
		turtle->setMoving(true);
		turtle->setDirection(LEFT);
		turtle->jumping_speed = 0;
		created[2] = 1;
	}
	
}
void Game::shot() {
	
	if (cur_state != RUNNING)
		return;

	if (mario->pos().x() < (17 * 16))
	{
		BulletBill *shotted;
		shotted = new BulletBill(QPoint(20 * 16, 280), 1, LEFT);
		//instance()->getScene()->addItem(shotted);

		shotted->setMoving(true);
		shotted->setDirection(LEFT);
	}
	if (mario->pos().x() > (23 * 16) && mario->pos().x() < (36 * 16))
	{
		BulletBill *shotted;
		shotted = new BulletBill(QPoint(20 * 16, 280), 1, RIGHT);
		//instance()->getScene()->addItem(shotted);
		shotted->setMoving(true);
		shotted->setDirection(RIGHT);
	}
	if (mario->pos().x() > (23 * 16) && mario->pos().x() < (32 * 16))
	{
		BulletBill *shotted;
		shotted = new BulletBill(QPoint(35 * 16, 280), 2, LEFT);
		//instance()->getScene()->addItem(shotted);
		shotted->setMoving(true);
		shotted->setDirection(LEFT);
	}

	if (mario->pos().x() > (38 * 16) && mario->pos().x() < (48 * 16))
	{
		BulletBill *shotted;
		shotted = new BulletBill(QPoint(35 * 16, 280), 2, RIGHT);
		//instance()->getScene()->addItem(shotted);
		shotted->setMoving(true);
		shotted->setDirection(RIGHT);
	}
	if (mario->pos().x() > (73 * 16) && mario->pos().x() < (90 * 16))
	{
		BulletBill *shotted;
		shotted = new BulletBill(QPoint(87 * 16, 280), 1, LEFT);
		instance()->getScene()->addItem(shotted);
		shotted->setMoving(true);
		shotted->setDirection(LEFT);
	}

	if (mario->pos().x() > (90 * 16) && mario->pos().x() < (100 * 16))
	{
		BulletBill *shotted;
		shotted = new BulletBill(QPoint(87 * 16, 280), 1, RIGHT);
		//instance()->getScene()->addItem(shotted);
		shotted->setMoving(true);
		shotted->setDirection(RIGHT);
	}
	

}
void Game::start()
{

	if (cur_state == READY && life <= 3 && life >= 1)
	{
		scene->clear();
		engine.start();
		shots.start();
		piranhaa.start();
		turtleadd.start();
		//ciclo per azzerare il controllo sulle tartarughe
		for (int i =0; i < 3; i++)
			created[i] = 0;
		
		mario = LevelManager::load("World-8-3", scene);

		//inizializzazione Hammer
		hammer = LevelManager::load1();
		hammer2 = LevelManager::load2();
	
		//inizializzazione testo
		Testo::instance()->getScene()->setBackgroundBrush(QColor(99, 133, 251));
		Testo::instance()->start();
		centerOn(mario);
		
		music->play();
	
		cur_state = RUNNING;

	}

}

/*void Game::keyPressEvent(QKeyEvent *e)
{
// start new game
if (e->key() == Qt::Key_S && cur_state == READY)
start();
}
*/

//funzione per reset del gioco
void Game::goreset() {

	scene->clear();
	reset();
	Testo::instance()->time.stop();
	Testo::instance()->getScene()->setBackgroundBrush(Qt::black);
	piranhaa.stop();
	turtleadd.stop();
	//turtleadd.start();
	for (int i = 0; i < 3; i++)
		created[i] = 0;
	gamer.stop();
}

void Game::reset()
{
	cur_state = READY;
	centerOn(0, 0);

	for (int i = 0; i < 3; i++)
		created[i] = 0;

	//scene->clear();
	scene->setBackgroundBrush(QBrush(Qt::black));
	if (life >= 1) {

		//schermata di avvio del gioco
		QGraphicsTextItem* text = new QGraphicsTextItem();
		text->setPlainText("Press \"S\" to start a new game");
		text->setDefaultTextColor(Qt::white);
		text->setFont(QFont("Super Mario 256", 10));
		text->setPos(6 * 16, 200);
		text->setFlag(QGraphicsTextItem::ItemIsMovable, true);
		scene->addItem(text);

		QGraphicsTextItem* text1 = new QGraphicsTextItem();
		text1->setPlainText(QString::number(life));
		text1->setDefaultTextColor(Qt::white);
		text1->setFont(QFont("Super Mario 256", 8));
		text1->setPos(14.5 * 16, 135);
		text1->setFlag(QGraphicsTextItem::ItemIsMovable, true);
		scene->addItem(text1);

		QGraphicsTextItem* text3 = new QGraphicsTextItem();
		text3->setPlainText("X");
		text3->setDefaultTextColor(Qt::white);
		text3->setFont(QFont("Super Mario 256", 8));
		text3->setPos(13.5 * 16, 135);
		text3->setFlag(QGraphicsTextItem::ItemIsMovable, true);
		scene->addItem(text3);

		//Icona di Mario alla schermata principale
		QPixmap text_mario = loadTexture(":/graphics/mario-small-stand.png");
		QGraphicsPixmapItem* text_mario1;
		text_mario1 = new QGraphicsPixmapItem();
		text_mario1->setPixmap(text_mario);
		text_mario1->setPos(12 * 16, 135);
		scene->addItem(text_mario1);

		QGraphicsTextItem* text2 = new QGraphicsTextItem();
		text2->setPlainText("WORLD 8-3");
		text2->setDefaultTextColor(Qt::white);
		text2->setFont(QFont("Super Mario 256", 12));
		text2->setPos(10 * 16, 70);
		text2->setFlag(QGraphicsTextItem::ItemIsMovable, true);
		scene->addItem(text2);
	}
	else{
		QGraphicsTextItem* text2 = new QGraphicsTextItem();
		text2->setPlainText("GAME OVER");
		text2->setDefaultTextColor(Qt::white);
		text2->setFont(QFont("Super Mario 256", 12));
		text2->setPos(10 * 16, 135);
		text2->setFlag(QGraphicsTextItem::ItemIsMovable, true);

		scene->addItem(text2);
	}
}
// game over
void Game::gameover()
{
	// stop game
	cur_state = GAME_OVER;
	engine.stop();
	piranhaa.stop();
	shots.stop();
	turtleadd.stop();

	// set black background
	scene->setBackgroundBrush(QBrush(Qt::black));
	Testo::instance()->getScene()->setBackgroundBrush(Qt::black);
	// play game over sound
	QSound::play(":/sounds/gameover.wav");
	gamer.start();

}
//reset after die
void Game::reset_die()
{
	engine.stop();
	piranhaa.stop();
	shots.stop();
	//turtleadd.stop();
	gamer.start();
}
// pause / resume game
void Game::tooglePause()
{
	if (cur_state == RUNNING)
	{
		engine.stop();
		music->stop();
		cur_state = PAUSE;
		Testo::instance()->time.stop();
		QSound::play(":/sounds/pause.wav");
	}
	else if (cur_state == PAUSE)
	{
		engine.start();
		music->play();
		Testo::instance()->time.start();
		cur_state = RUNNING;
	}
}
// stop music
void Game::stopMusic()
{
	if (music)
	music->stop();
}
void Game::keyPressEvent(QKeyEvent *e)
{
	// start new game
	if (e->key() == Qt::Key_S && cur_state == READY)
	{
		start();
		Testo::instance()->point;
		Testo::instance()->time.start();
		Testo::instance()->ctime=300;
	}

	// reset game
	if (e->key() == Qt::Key_R /*|| cur_state == GAME_OVER*/)
	{
		music->stop();
		life = 3;
		goreset();
		
	}
	

	// pause game
	if (e->key() == Qt::Key_P)
		tooglePause();

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;
	
		// horizontal Mario's movements
		if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
		{
			mario->setMoving(true);
			mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);

		}
	
			
	// Mario's jump
	if (e->key() == Qt::Key_Space)
	{
		mario->jump();
	
	}

	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(true);

	
	//Mario shots fire
	if (mario->isFire() && e->key() == Qt::Key_X)
	{

		if (mario->dir == RIGHT) {
			new FireBall(QPoint(mario->pos().x() + 17, mario->pos().y()+16), mario->dir);
		}
		
		if(mario->dir==LEFT)
		{
			new FireBall(QPoint(mario->pos().x()-17, mario->pos().y() + 16), mario->dir);
		}
	}

	if (e->key() == Qt::Key_Q) {

		mario->setFire();
		mario->setTransforming();
	}
}
void Game::keyReleaseEvent(QKeyEvent *e)
{
	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
	{ 
		mario->setMoving(false);
	}

	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(false);
}

// zoom-in/out
void Game::wheelEvent(QWheelEvent *e)
{
	if (e->delta() > 0)
		scale(1.1, 1.1);
	else
		scale(1 / 1.1, 1 / 1.1);
}

void Game::advance()
{
	// do nothing if game is not running
	if (cur_state != RUNNING)
		return;

	// if mario is dead, game over
	if (mario->isDead())
	{
		life--;
		reset_die();
	}

	// if mario is dying or transforming, animate/advance only him
	// (the rest of the world is freezed)
	if (mario->isDying() || mario->isTransforming())
	{
		mario->animate();
		mario->advance();
		return;
	}

	// tell all game objects to animate and advance in the scene
	for (auto & item : scene->items())
	{
		Object* obj = dynamic_cast<Object*>(item);
		if (obj)
		{
			obj->animate();
			obj->advance();

			// destroy died Entity objects
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			if (entity_obj && entity_obj->isDead())
			{
				//printf("%s (%.0f,%.0f) destroyed\n", entity_obj->name().c_str(), entity_obj->pos().x(), entity_obj->pos().y());
				scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
	}

	// center view on Mario
	centerOn(mario);
}
