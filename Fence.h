#pragma once

#include "Inert.h"

class Fence : public Inert {


public:

	Fence(QRect rect);

	virtual std::string name() { return "Fence"; }
	virtual void hit(Object *what, Direction fromDir) { /* do nothing */ }
};