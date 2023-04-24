#pragma once

#include "Inert.h"

class Castel : public Inert {


public:

	Castel(QRect rect, int size);

	virtual std::string name() { return "Castel"; }
	virtual void hit(Object *what, Direction fromDir) { /* do nothing */ }
};