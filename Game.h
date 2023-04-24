#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QSound>
#include "Object.h"
#include "LevelManager.h"
#include "Block.h"
#include "Mario.h"
#include "Canon.h"
#include "Pipe.h"
#include  "Brick.h" 
#include "Testo.h"


class Game : public QGraphicsView
{
	Q_OBJECT
		enum game_state { READY, RUNNING, PAUSE, GAME_OVER };

private:

	static Game* uniqueInstance;     // Singleton design pattern
	Game(QWidget* parent = nullptr);	// Singleton design pattern
	
	QTimer engine,shots, piranhaa, timerpos, gamer, turtleadd;
	Block* oggetto;
	QGraphicsScene *scene;          // the scene used to render the game (2D)
	Mario *mario;
	Hammer* hammer, * hammer2;
	int endLevelCoord;

	int created[3];

	
	
public:
	// get unique instance
	game_state cur_state;
	QSound* music;
	static Game* instance(QWidget* parent = 0);
	Mario* getMario() { return mario; }
	Hammer* getHammer() { return hammer; }
	Hammer* getHammer2() { return hammer2; }
	int getEndLevel() { return endLevelCoord; }

	QGraphicsTextItem* tes;
	int life=3;
	// getters
	QGraphicsScene* getScene() { return scene; }
protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void keyReleaseEvent(QKeyEvent *e);

	// zoom-in/out
	virtual void wheelEvent(QWheelEvent *e);
public slots:
	// advance game / next frame
	void advance();
	
	// pause / resume game
	void tooglePause();

	void goreset();

	// reset game
	void reset();

	//reset after die
	void reset_die();

	// start new game
	void start();

	// game over
	void gameover();

	// stop music
	void stopMusic();

	//shot hammer
	void shot();

	//start piranha
	void piranha();

	//start turtle
	void addturtle();
};