/*
 * orbit - a small orbiter, orbiting the player node
 */
#include "../nodes.h"

void orbit_init(node *this)
{
	this->node_actor = at_tet_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void orbit_free(node *this)
{
	node_free(this);
	
	return;
}

void orbit_collision(node *this)
{
	/* do nothing */
	
	return;
}

void orbit_applyconstraints(node *this)
{	
	/* normalize angles */
	normalize_ang(this->rotation.x);
	normalize_ang(this->rotation.y);
}

void orbit_render(node *this)
{
	/* draw node */
	slPushMatrix();
		slTranslate(toFIXED(this->position.x), toFIXED(this->position.y), toFIXED(-this->position.z));
		slScale(toFIXED(0.05), toFIXED(0.05), toFIXED(0.05));
		actor_render(this->node_actor);
	slPopMatrix();
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
	return;
}

void orbit_routine(node *this)
{
	switch (this->routine_index) {
		case NR_INIT:
			orbit_init(this);
			break;
		case NR_FREE:
			orbit_free(this);
			break;
		case NR_COLLIDE:
			orbit_collision(this);
			break;
		case NR_ORBIT_CONSTRAINT:
			orbit_applyconstraints(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			break;
	}
	
	return;
}
