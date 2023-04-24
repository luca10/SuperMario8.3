#include "Mario.h"
#include "Enemy.h"
#include "Game.h"
#include <QSound>

Mario::Mario(QPoint position) : Entity()
{
	// set flags
	moving = false;
	running = false;
	bouncing = false;
	big = false;
	fire = false;
	transforming = false;
	sliding = false;
	transformation_counter = 0;
	life = 3;
	// durations
	jumping_duration = jump_duration_small;
	death_duration = 300;
	transformation_duration = freeze_duration;

	// textures
	texture_walk[0][0] = QPixmap(loadTexture(":/graphics/mario-small-walk-0.png"));
	texture_walk[0][1] = QPixmap(loadTexture(":/graphics/mario-small-walk-1.png"));
	texture_walk[0][2] = QPixmap(loadTexture(":/graphics/mario-small-walk-2.png"));
	texture_walk[1][0] = QPixmap(loadTexture(":/graphics/mario-big-walk-0.png"));
	texture_walk[1][1] = QPixmap(loadTexture(":/graphics/mario-big-walk-1.png"));
	texture_walk[1][2] = QPixmap(loadTexture(":/graphics/mario-big-walk-2.png"));
	texture_walk[2][0] = QPixmap(loadTexture(":/graphics/mario2_move0.bmp"));
	texture_walk[2][1] = QPixmap(loadTexture(":/graphics/mario2_move1.bmp"));
	texture_walk[2][2] = QPixmap(loadTexture(":/graphics/mario2_move2.bmp"));
	texture_stand[0] = QPixmap(loadTexture(":/graphics/mario-small-stand.png"));
	texture_stand[1] = QPixmap(loadTexture(":/graphics/mario-big-stand.png"));
	texture_stand[2] = QPixmap(loadTexture(":/graphics/mario2.bmp"));
	texture_jump[0] = QPixmap(loadTexture(":/graphics/mario-small-jump.png"));
	texture_jump[1] = QPixmap(loadTexture(":/graphics/mario-big-jump.png"));
	texture_jump[2] = QPixmap(loadTexture(":/graphics/mario2_jump.bmp"));
	texture_dead = QPixmap(loadTexture(":/graphics/mario-small-fall.png"));
	texture_small_to_big[0] = texture_stand[0];
	texture_small_to_big[1] = QPixmap(loadTexture(":/graphics/mario-med-stand.bmp"));
	texture_small_to_big[2] = texture_stand[1];
	texture_small_to_big[3] = QPixmap(loadTexture(":/graphics/mario-med-stand.bmp"));
	texture_big_to_fire[0] = texture_stand[1];
	texture_big_to_fire[1] = QPixmap(loadTexture(":/graphics/mario2_med.bmp"));
	texture_big_to_fire[2] = texture_stand[2];
	texture_big_to_fire[3] = QPixmap(loadTexture(":/graphics/mario2_med.bmp"));
	texture_hang[0]= QPixmap(loadTexture(":/graphics/mario-small-hang-0.png"));
	texture_hang[1]= QPixmap(loadTexture(":/graphics/mario-small-hang-1.png"));
	texture_hang[2]= QPixmap(loadTexture(":/graphics/mario-big-hang-0.png"));
	texture_hang[3]= QPixmap(loadTexture(":/graphics/mario-big-hang-1.png"));
	texture_hang[4]= QPixmap(loadTexture(":/graphics/mario2_end.bmp"));
	texture_hang[5]= QPixmap(loadTexture(":/graphics/mario2_end1.bmp"));

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_stand[0]);
	setPos(position - QPoint(0, pixmap().height()));

	// Mario is at a higher layer than other objects
	setZValue(3);
}

// Mario jumps
void Mario::jump()
{
	// do nothing if already jumping
	if (jumping)
		return;

	startJumping();

	if (jumping)
		QSound::play(big ? ":/sounds/jump-big.wav" : ":/sounds/jump-small.wav");

}

// Mario eats a (red = default) Mushroom and gets big
void Mario::mushroomEat(bool red)
{
	if (red)
	{

		Testo::instance()->update_points(1000);
		// get big if not already
		if (!big )
		{
			big = true;

			// set proper jump duration
			jumping_duration = jump_duration_big;

			// start transformation
			startTransformation();
		}

		// play sound in any case
		QSound::play(":/sounds/mushroom-eat.wav");
	}
	// green: life up
	else
		QSound::play(":/sounds/oneup.wav");
}

// Mario eats a Flower and can fire
void Mario::flowerEat()
{
	Testo::instance()->update_points(1000);

	if (!fire)
	{
		fire = true;
		big = false;
		// set proper jump duration
		jumping_duration = jump_duration_big;

		// start transformation
		startTransformation();
	}

	// play sound in any case
	QSound::play(":/sounds/mushroom-eat.wav");

	// to be implemented
	QSound::play(":/sounds/mushroom-eat.wav");
}

// Mario is hurt
void Mario::hurt()
{
	// cannot fire anymore

	//if fire,gets big
	if(fire){
		
		fire = false;
		big = true;
	
		// set proper jump duration
		jumping_duration = jump_duration_small;

		// play sound
		QSound::play(":/sounds/shrink.wav");

		// Mario becomes a phantom temporarily
		startPhantom();

		// start transformation
		startTransformation();

	
	}
	else {
		// if big, gets small
		if (big)
		{
			big = false;

			// set proper jump duration
			jumping_duration = jump_duration_small;

			// play sound
			QSound::play(":/sounds/shrink.wav");

			// Mario becomes a phantom temporarily
			startPhantom();

			// start transformation
			startTransformation();
		}
		// otherwise, Mario dies
		else
			die();
	}
}

// start transformation
void Mario::startTransformation()
{
	// start transformation
	transforming = true;

	// set animation counter so that next animation
	// is properly handled (see animate())
	transformation_counter = big ? 0 : 2 * transf_div;
	transformation_counter = fire ? 0 : 2 * transf_div;
	moveBy(0,-16);
	// freeze
	freeze();
}

// end transformation
void Mario::endTransformation()
{
	// end transformation
	transforming = false;

	// reset animation counter
	transformation_counter = 0;

	// correct y coordinate so that the 'final' (transformed) Mario
	// has the same bottom coordinate  
	if (big) {
		int dy = pixmap().height() - (big ? texture_stand[1] : texture_stand[0]).height();
		setY(y() + (2 * dy));
	}
}


void Mario::animate()
{
	// handle bouncing
	if (jumping == false && bouncing)
	{
		bouncing = false;
		jumping_duration = big ? jump_duration_big : jump_duration_small;
	}
	// handle phantom mode
	if (phantom)
	{
		phantom_counter++;
		if (phantom_counter > phantom_duration)
			endPhantom();
	}

	// handle transformation
	if (transforming)
	{
		transformation_counter++;
		if (transformation_counter > transformation_duration)
			endTransformation();
	}

	// set proper texture
	if (transforming)
	{
		int prev = ((transformation_counter - 1) / transf_div) % 4;
		int curr = (transformation_counter / transf_div) % 4;
		if (big) {
			int dy = texture_small_to_big[prev].height() - texture_small_to_big[curr].height();
			setPixmap(texture_small_to_big[(transformation_counter / transf_div) % 4]);
			setY(y() + dy);
		}
		if (fire) {
			int dy = texture_big_to_fire[prev].height() - texture_big_to_fire[curr].height();
			setPixmap(texture_big_to_fire[(transformation_counter / transf_div) % 4]);
			setY(y() + dy);
		}
	}
	else if (dying || dead)
		setPixmap(texture_dead);
	else if (end)
	{
		if (!transforming)
			setPixmap(texture_hang[0]);
		if(big)
			setPixmap(texture_hang[2]);
		if(fire)
			setPixmap(texture_hang[4]);
		
	}
	else if (moving && !jumping && !falling) {
		if (big)
			setPixmap(texture_walk[1][(walk_counter++ / (running ? running_div : walk_div)) % 3]);
		if (fire)
			setPixmap(texture_walk[2][(walk_counter++ / (running ? running_div : walk_div)) % 3]);
		if(!big && !fire)
			setPixmap(texture_walk[0][(walk_counter++ / (running ? running_div : walk_div)) % 3]);
		
	}
	else if (jumping || falling) {
		if(big)
			setPixmap(texture_jump[1]);
		if (fire)
			setPixmap(texture_jump[2]);
		if (!big && !fire)
			setPixmap(texture_jump[0]);
	}
	else {
		if (big)
			setPixmap(texture_stand[1]);
		if (fire)
			setPixmap(texture_stand[2]);
		if (!big && !fire)
			setPixmap(texture_stand[0]);
	}

	// mirror the texture along the horizontal axis if needed
	if (dir == LEFT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

// Mario has been hit
void Mario::hit(Object *what, Direction fromDir)
{
	// if hit by Enemy
	Enemy *enemy = dynamic_cast<Enemy*>(what);
	if (enemy)
	{
		// with Mario's feet and enemy is hurtable --> enemy is hurt
		if (fromDir == DOWN && enemy->isHurtable())
		{
			// hurt enemy and bounce
			enemy->hurt();
			bounce();
		}
		// all other cases   --> Mario is hurt
		else
			hurt();
	}
}

// bounce on enemies
void Mario::bounce()
{
	falling = false;
	bouncing = true;
	jumping_duration = jump_duration_tiny;
	startJumping();
}

// override die method so we can play Mario death animation
void Mario::die()
{
	// call superclass method
	Entity::die();

	// in addition, we make Mario not collidable
	// so he can fall through all objects (including Terrain)
	collidable = false;

	// play death sound while stopping level music
	QSound::play(":/sounds/death.wav");
	Game::instance()->stopMusic();
	Testo::instance()->time.stop();
	
	// freeze Mario before jumping
	freeze();

	// make a slow jump
	jumping_speed = 2;
	falling_speed = 1;
	startJumping();
}


// running = double moving speed
void Mario::setRunning(bool _running)
{
	// do nothing if running state does not change
	if (running == _running)
		return;

	// set new running state
	running = _running;

	// double / halve moving speed
	if (running)
		moving_speed *= 2;
	else
		moving_speed /= 2;
}
void Mario::startSlide()
{
	end = true;
	jumping = true;
	jump_counter = 0;
	falling = false;
	sliding = true;
	
	//prevPos = pos();
	setX(x());
	solveCollisions();
}
void Mario::endSlide()
{
	sliding = false;
	freezed = false;
	setX(x() + 1);
	end = false;
	Testo::instance()->add_end();
	setMoving(true);
	falling = true;
	dir = RIGHT;

	
}
