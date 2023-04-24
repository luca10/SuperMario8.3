#include <QApplication>
#include "Game.h"
#include "Testo.h"
#include "Mario.h"



int main(int argc, char *argv[])
{
	// create Qt application
	QApplication app(argc, argv);
	QWidget* game_window = new QWidget(0);

	game_window->setFixedSize(928, 624);

	// create and show the game
	Game::instance(game_window);
	
	Testo::instance(game_window);
	Testo::instance()->getScene()->setBackgroundBrush(Qt::black);
	
	game_window->show();


	// launch Qt event loop
	return app.exec();
}

