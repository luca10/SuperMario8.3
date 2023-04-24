#pragma once

#include "Inert.h"
#include "QTimer.h"
#include "Testo.h"

#include "Background.h"

class Pole : public Inert
{
Q_OBJECT
	private:

		Background* endpole;
		Background* flag;

		bool hitted;
		int hit_counter;
		int hit_duration;
		bool ended;
		int check=0;
	public:

		Pole(QPoint position);
		QGraphicsTextItem* text;
		QTimer textT, end_level;
		int textTimeCounter = 0;
		int textTimeCounter1 = 0;
		int textTimeCounter2 = 0;
		// pure virtual methods that must be implemented
		virtual std::string name() { return "Pole"; }
		virtual void hit(Object *what, Direction fromDir);
		void advance();
public slots:
	void settext();
	void end();
};
