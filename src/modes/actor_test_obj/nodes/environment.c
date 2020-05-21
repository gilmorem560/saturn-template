/*
 * environment - the world environment
 */
#include "../nodes.h"

void environment_init(node *this)
{
	this->node_actor = at_cube_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void environment_free(node *this)
{
	node_free(this);
	
	return;
}

void environment_collision(node *this)
{
	unsigned short index;
	unsigned short node;
	collided has_collided = {0, 0, 0};
	
	/* act on previous collisions by object type */
	/* environment likely won't have any, environment is typically root node */
	for (index = 0; index < this->collisions_count; index ++) {
		node = this->collisions[index].id;
		switch (graph->nodes[node]->type) {
		default:
			break;
		}
	}
	node_clearcollisions(this);
	
	/* calculate collisions with objects and notify them */
	for (index = 0; index < graph->node_count; index++) {
		if (graph->nodes[index]->position.x < -2.9)
			has_collided.x = -1;
		else if (graph->nodes[index]->position.x > 2.9)
			has_collided.x = 1;

		if (graph->nodes[index]->position.y < -2.9)
			has_collided.y = -1;
		else if (graph->nodes[index]->position.y > 2.9)
			has_collided.y = 1;
	
		if (graph->nodes[index]->position.z < -11.0)
			has_collided.z = -1;
		else if (graph->nodes[index]->position.z > -1.1)
			has_collided.z = 1;
		
		node_addcollision(graph->nodes[index], this, has_collided);
		
		has_collided.x = 0;
		has_collided.y = 0;
		has_collided.z = 0;
	}
	
	/* act on collisions */
	/* environment does not react, only informs */
	for (index = 0; index < this->children_count; index++) {
		node_routine(this->children[index], NR_COLLIDE);
	}
	
	return;
}

void environment_render(node *this)
{
		/* draw wall */
		slPushMatrix();
			slTranslate(toFIXED(-2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( -2.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 2.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 2.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(-2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(-2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
		slPopMatrix();
		/* draw floor */
		slPushMatrix();
			slTranslate(toFIXED(-2.0), toFIXED( -4.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
		slPopMatrix();
		/* draw walls */
		slPushMatrix();
			slRotZ(DEGtoANG(90.0));
			/*glRotated(90.0), toFIXED( 0.0), toFIXED( 0.0), toFIXED( 1.0)); */
			slTranslate(toFIXED(-2.0), toFIXED( -4.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
		slPopMatrix();
		slPushMatrix();
			slRotZ(DEGtoANG(-90.0));
			/*glRotated(90.0), toFIXED( 0.0), toFIXED( 0.0), toFIXED( -1.0)); */
			slTranslate(toFIXED(-2.0), toFIXED( -4.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
		slPopMatrix();
		/* draw ceiling */
		slPushMatrix();
			slRotZ(DEGtoANG(180.0));
			/*glRotated(180.0), toFIXED( 0.0), toFIXED( 0.0), toFIXED( 1.0)); */
			slTranslate(toFIXED(-2.0), toFIXED( -4.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( -2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(2.0), toFIXED( 0.0), toFIXED( 0.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
			slTranslate(toFIXED(0.0), toFIXED( 0.0), toFIXED( 2.0));
			at_cube_render(this->node_actor);
		slPopMatrix();
		
		return;
}

void environment_routine(node *this)
{
	switch (this->routine_index) {
		case NR_NULL:
			break;
		case NR_INIT:
			environment_init(this);
			break;
		case NR_FREE:
			environment_free(this);
			break;
		case NR_COLLIDE:
			environment_collision(this);
			break;
		default:
			break;
	}
	
	return;
}
