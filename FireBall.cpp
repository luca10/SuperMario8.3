#include "FireBall.h"
#include "Game.h"




FireBall::FireBall(QPoint position,Direction dir)
{
	texture_walk[0] = QPixmap(loadTexture(":/graphics/fireball_0.bmp"));
	texture_walk[1] = QPixmap(loadTexture(":/graphics/fireball_1.bmp"));
	texture_walk[2] = QPixmap(loadTexture(":/graphics/fireball_2.bmp"));
	texture_walk[3] = QPixmap(loadTexture(":/graphics/fireball_3.bmp"));
	texture_end = QPixmap(loadTexture(":/graphics/firework2.bmp"));
	collidable = true;
	falling = true;
	jumping_speed = 1;
	moving_speed = 2;
	setPixmap(texture_walk[0]);
	setPos(position);
	setDirection(dir);

	//setZValue(3);
}


 void FireBall::animate(){
   
	 if(moving==true)
	 setPixmap(texture_walk[(walk_counter++ / walk_div) % 4]);
	 
 }
 void FireBall::hit(Object* what, Direction fromDir){

	  if(dynamic_cast<Enemy*>(what))
		  die();
	  
	  if (what->isWalkable()) 
	 {
       
		if(fromDir == DOWN)
		 {
			jump_counter = 16;
			 falling = false;
			 startJumping();
		 }
        if(fromDir==LEFT || fromDir==RIGHT)
		die();
		 
	 }

 }

 void FireBall::die() {

	 moving = false;
	 jumping = false;
	 death_duration = 20;
	 setPixmap(texture_end);
	 Entity::die();

 }