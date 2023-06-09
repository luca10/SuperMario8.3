#pragma once

#include <string>
#include <QGraphicsPixmapItem>


#include "Utils.h"

class Object : public QGraphicsPixmapItem {

protected:
	bool walkable;
	bool collidable;

public:
	Object(); 
	
	// getters
	bool isWalkable() { return walkable; }
	bool isCollidable() { return collidable; }

	int helpme = 0;
	int helpme1 = 1;

	
	// object name
	virtual std::string name() = 0;


	// animate (=compute next texture)
	virtual void animate() = 0;

	// advance (=compute next location)
	virtual void advance() = 0;

	// solve collisions
	virtual void solveCollisions() = 0;

	// object hit by 'what' from direction 'fromDir'
	virtual void hit(Object *what, Direction fromDir) = 0;

	// utility methods: detect collision/touching direction
	virtual Direction collisionDirection(Object* item);
	virtual Direction touchingDirection(Object* item);
};