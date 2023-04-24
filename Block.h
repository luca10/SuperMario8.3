#pragma once

#include "Inert.h"
#include "Utils.h"


class Block : public Inert {

    public:
	
	Block(QRect rect);

	virtual std::string name() { return "Block"; }

	virtual void hit(Object *what, Direction fromDir) { /* do nothing */ };

};