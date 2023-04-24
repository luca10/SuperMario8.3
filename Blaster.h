#include "Inert.h"
#include "Entity.h"

class Blaster : public Inert {

public:

	 Blaster(QPoint Position, int size);

	 virtual std::string name() { return "Blaster"; }
	 virtual void hit(Object *what, Direction fromDir) { /* do nothing */ };
};