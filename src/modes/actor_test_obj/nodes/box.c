/*
 * box - a box you can stand on!
 */
#include "../nodes.h"

void box_init(node *this)
{
	this->node_actor = at_cube_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void box_free(node *this)
{
	node_free(this);
	
	return;
}

void box_collision(node *this)
{
	/* do nothing */
	
	return;
}

void box_applyconstraints(node *this)
{	
	/* normalize angles */
	normalize_ang(this->rotation.x);
	normalize_ang(this->rotation.y);
}

void box_render(node *this)
{
	/* draw node */
	slPushMatrix();
		slTranslate(toFIXED(this->position.x), toFIXED(this->position.y), toFIXED(-this->position.z));
		slScale(toFIXED(0.5), toFIXED(0.5), toFIXED(0.5));
		actor_render(this->node_actor);
	slPopMatrix();
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
	return;
}

void box_routine(node *this)
{

	switch (this->routine_index) {
		case NR_INIT:
			box_init(this);
			break;
		case NR_FREE:
			box_free(this);
			break;
		case NR_COLLIDE:
			box_collision(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			break;
	}
	
	return;
}
