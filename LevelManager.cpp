#include<iostream>
#include"LevelManager.h"
#include"Brick.h"
#include"Block.h"
#include"Canon.h"
#include"Terrain.h"
#include"Box.h"
#include"Blaster.h"
#include"Background.h"
#include "Fence.h"
#include "Game.h"
#include "Pipe.h"
#include "Castel.h"
#include "Mario.h"
#include "Turtle.h"
#include "Piranha.h"
#include "Testo.h"
#include "Hammer.h"
#include "FireBall.h"
#include "Pole.h"
#include <QDebug>
#include <QTextEdit>

Mario* LevelManager::load(std::string level_name, QGraphicsScene * scene) {

	Mario* mario=0;

	if (level_name == "World-8-3") {

		scene->setBackgroundBrush(QBrush(QColor(99, 133, 251)));

		int terrain_level = 280;
	
		new Terrain(QRect(0,terrain_level,69 *16, 32));
		new Pipe(QPoint(-16, terrain_level), 3);
		new Pipe(QPoint(-16, terrain_level-64), 3);
		new Background(QPoint(0,terrain_level),":/graphics/World8.3/castle.png");
	    new Background(QPoint(0.5*16, terrain_level-128), ":/graphics/World8.3/cloud-med.png");
		new Background(QPoint(11*16, terrain_level), ":/graphics/World8.3/tree_0.bmp");
		new Background(QPoint(13 *16, terrain_level), ":/graphics/World8.3/tree_1.bmp");
		new Fence(QRect(14*16, terrain_level-16,4*16, 16));
		new Blaster(QPoint(18 * 16, terrain_level), 0);
		new Background(QPoint(19 * 16, terrain_level - 8*16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(21 * 16, terrain_level), ":/graphics/World8.3/tree_1.bmp");
		new Background(QPoint(23 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");

		new Castel(QRect(24 * 16, terrain_level - 80, 8*16, 80),0);
		new Castel(QRect(24 * 16, terrain_level - 96, 8*16,16), 1);
		
		new Background(QPoint(28 * 16, terrain_level - 9*16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(31 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");
		new Blaster(QPoint(34 * 16, terrain_level), 1);

		new Castel(QRect(37 * 16, terrain_level - 80, 14 * 16, 80), 0);
		new Castel(QRect(37 * 16, terrain_level - 96, 14 * 16, 16), 1);

		new Background(QPoint(46 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(49 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");

		new Pipe(QPoint(54 * 16, terrain_level), 3);

		new Brick(QPoint(60 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(61 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(62 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(63 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(64 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(65 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(66 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(67 * 16, terrain_level - 4 * 16));

		new Brick(QPoint(60 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(61 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(62 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(63 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(64 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(65 * 16, terrain_level - 8 * 16));
		new Box(QPoint(66 * 16, terrain_level - 8 * 16), BRICKED, POWERUP);
		new Brick(QPoint(67 * 16, terrain_level - 8 * 16));

		new Background(QPoint(59 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");
		new Background(QPoint(61 * 16, terrain_level), ":/graphics/World8.3/tree_1.bmp");

		new Fence(QRect(62 * 16, terrain_level - 16, 4 * 16, 16));



		new Background(QPoint(66.5 * 16, terrain_level-8.5*16), ":/graphics/World8.3/cloud-small.png");
		new Terrain(QRect(71*16, terrain_level, 4 * 16, 32));

		new Block(QRect(71 * 16, terrain_level-64, 16,64 ));
		new Block(QRect(72 * 16, terrain_level - 48, 16, 48));
		new Block(QRect(73 * 16, terrain_level - 32, 16, 32));
		new Block(QRect(74 * 16, terrain_level - 16, 16, 16));

		new Terrain(QRect(77 * 16, terrain_level, 47 * 16, 32));

		new Background(QPoint(75 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");

		new Castel(QRect(79 * 16, terrain_level - 80, 6 * 16, 80), 0);
		new Castel(QRect(79 * 16, terrain_level - 96, 6 * 16, 16), 1);

		new Background(QPoint(78 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");
		new Blaster(QPoint(86 * 16, terrain_level), 0);
		new Fence(QRect(87 * 16, terrain_level - 16, 16, 16));

		new Castel(QRect(88 * 16, terrain_level - 80, 6 * 16, 80), 0);
		new Castel(QRect(88 * 16, terrain_level - 96, 6 * 16, 16), 1);

		new Block(QRect(95 * 16, terrain_level - 46, 16, 46));
		new Background(QPoint(93.5 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(97 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");

		new Castel(QRect(97 * 16, terrain_level - 80, 10 * 16, 80), 0);
		new Castel(QRect(97 * 16, terrain_level - 96, 10 * 16, 16), 1);

		new Background(QPoint(107 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");

		new Block(QRect(109 * 16, terrain_level - 64, 16, 64));
		new Block(QRect(110 * 16, terrain_level - 64, 16, 64));

		new Fence(QRect(111 * 16, terrain_level - 16, 3*16, 16));

		new Background(QPoint(117 * 16, terrain_level), ":/graphics/World8.3/tree_1.bmp");
		new Background(QPoint(119 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");
		new Background(QPoint(120 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");

		new Brick(QPoint(115 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(116 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(117 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(118 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(119 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(120 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(121 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(122 * 16, terrain_level - 4 * 16));

		new Brick(QPoint(115 * 16, terrain_level - 8 * 16));
		new Box(QPoint(116 * 16, terrain_level - 8 * 16), BRICKED, POWERUP);
		new Brick(QPoint(117 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(118 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(119 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(120 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(121 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(122 * 16, terrain_level - 8 * 16));
	

		new Background(QPoint(113.5 * 16, terrain_level - 8.3 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(123.5 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(126.5 * 16, terrain_level -  8 * 16), ":/graphics/World8.3/cloud-med.png");

		new Terrain(QRect(126 * 16, terrain_level, 2 * 16, 32));
		new Terrain(QRect(130 * 16, terrain_level, 66 * 16, 32));

		new Pipe(QPoint(127 * 16, terrain_level), 3);

		new Castel(QRect(132 * 16, terrain_level - 80, 34* 16, 80), 0);
		new Castel(QRect(132 * 16, terrain_level - 96, 34 * 16, 16), 1);

		new Background(QPoint(143 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(146 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");
		new Background(QPoint(163.5 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(167 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");
		new Pipe(QPoint(169 * 16, terrain_level), 1);

		new Castel(QRect(171 * 16, terrain_level - 80, 20 * 16, 80), 0);
		new Castel(QRect(171 * 16, terrain_level - 96, 20 * 16, 16), 1);

		new Background(QPoint(170 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(173 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");

		new Background(QPoint(188.5 * 16, terrain_level - 9 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(191.5 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-med.png");
		new Background(QPoint(189 * 16, terrain_level - 3 * 16), ":/graphics/World8.3/brickred.bmp");
		//new Background(QPoint(6 * 16, terrain_level - 3 * 16), ":/graphics/World8.3/brickred.bmp");
		//new Brick(QPoint(6 * 16, terrain_level - 4 * 16));
		new Box(QPoint(189 * 16, terrain_level - 4 * 16), BRICKED, COIN);

		new Block(QRect(194 * 16, terrain_level - 32, 16, 32));
		new Block(QRect(197 * 16, terrain_level - 32, 16, 16));
		new Block(QRect(199 * 16, terrain_level - 64, 16, 16));
		new Block(QRect(201 * 16, terrain_level - 96, 16, 16));
		new Block(QRect(203 * 16, terrain_level - 128, 2*16, 16));

		new Terrain(QRect(207 * 16, terrain_level, 80 * 16, 32));
		new Fence(QRect(207 * 16, terrain_level - 16, 2*16, 16));

		

		new Brick(QPoint(67 * 16, terrain_level - 8 * 16));
		new Background(QPoint(212 * 16, terrain_level), ":/graphics/World8.3/tree_1.bmp");
		new Background(QPoint(210 * 16, terrain_level - 8 * 16), ":/graphics/World8.3/cloud-small.png");
		new Block(QRect(213 * 16, terrain_level - 16, 16, 16));
		new Pole(QPoint(213 * 16, terrain_level - 1 * 16));
		new Background(QPoint(214 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");
		new Background(QPoint(215 * 16, terrain_level), ":/graphics/World8.3/tree_0.bmp");

		new Background(QPoint(216.5 * 16, terrain_level - 10 * 16), ":/graphics/World8.3/cloud-small.png");
		new Background(QPoint(219*16, terrain_level), ":graphics/World8.3/end_castel.png");

		mario = new Mario(QPoint(1*16, terrain_level-32));
		
	
	}	
	return mario;
}
Hammer* LevelManager::load1()
{
	Hammer* showw1 = 0;
	Hammer* showw2 = 0;
	Hammer* showw3 = 0;
	Hammer* showw4 = 0;

	showw1 = new Hammer(QPoint(67 * 16, 248 - 8 * 16), LEFT);
	showw2 = new Hammer(QPoint(123 * 16, 248-8*16), LEFT);
	showw3 = new Hammer(QPoint(154 * 16, 248-8*16), LEFT);
	showw4 = new Hammer(QPoint(178 * 16, 280), LEFT);



	return showw1, showw2, showw3, showw4;
}

Hammer* LevelManager::load2()
{
	Hammer* showw2 = 0;
	Hammer* showw3 = 0;
	Hammer* showw4 = 0;
	Hammer* showw5 = 0;

	
	showw2 = new Hammer(QPoint(64 * 16, 280), LEFT);
	showw3 = new Hammer(QPoint(120 * 16, 280), RIGHT);
	showw4 = new Hammer(QPoint(150 * 16, 280), RIGHT);
	showw5 = new Hammer(QPoint(185 * 16, 280), RIGHT);


	return showw2, showw3, showw4, showw5;
}
