#pragma once

#include "Enemy.h"
#include <QObject>
#include "QTimer.h"
#include "Canon.h"
#include <QSound>
#include <QtWidgets>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
class Testo :public QGraphicsView
{
	Q_OBJECT
private:
	static Testo* uniqueInstance;	// Singleton design pattern
	Testo(QWidget* parent = nullptr);

	QGraphicsScene* scene;            // the scene used to render the hud 
	QGraphicsPixmapItem* main_screen;
	static const int walk_div = 10;
	QPixmap texture_cycle[4];
	
public:
	QTimer time, fine;	
	int ctime, cpoint, coin;
	QPixmap textcoin;
	QGraphicsTextItem* time_ui, *point, *Ccoin;
	QGraphicsPixmapItem* test01;
	QSound* music;
	int walk, mus=0;
	int help_point=0, help_point1=0;
	static Testo* instance(QWidget* parent = nullptr);

	QGraphicsScene* getScene() { return scene; }

	void start();
	void update_points(int cpoint);
	void update_coin(int coin);

public slots:
	void update_ui();
	void add_end();
	void set_end_point();
	
};