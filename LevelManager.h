#pragma once

#include <QGraphicsScene>
#include <string>
#include <QObject>
#include "Mario.h"
#include "QTimer.h"
#include "Hammer.h"
#include "Testo.h"

class LevelManager
{
public:
	
	// load all items from the given level in the given scene
	// also returns the Mario object
	static Mario* load(std::string level_name, QGraphicsScene * scene);
	static Hammer* load1();
	static Hammer* load2();

};
