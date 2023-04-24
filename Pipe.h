#pragma once
#include "Inert.h"
#include "Enemy.h"
#include "Object.h"
#include <QObject>
#include "QTimer.h"


class Pipe :Inert
{

Q_OBJECT

public: 
	Pipe(QPoint Position,int size);

	virtual std::string name() { return "Pipe"; };
	virtual void hit(Object *what, Direction fromDir) { /* do nothing */ };
};