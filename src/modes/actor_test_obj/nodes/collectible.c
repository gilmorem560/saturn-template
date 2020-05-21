/*
 * collectible - a collectible you can grab!
 */
#include "../nodes.h"

void collectible_init(node *this)
{
	this->node_actor = at_triangle_new();
	actor_routine(this->node_actor, AR_INIT);
	
	return;
}

void collectible_free(node *this)
{
	node_free(this);
	
	return;
}

void collectible_collision(node *this)
{
	unsigned int index;
	signed int node;
	
	/* do nothing */
	/* act on previous collisions by object type */
	for (index = 0; index < this->collisions_count; index++) {
		node = this->collisions[index].id;
		switch (graph->nodes[node]->type) {
		case NT_PLAYER:
			if (this->collisions[index].x == 1)
				scene_switchactivenode(graph, this->id);
			break;
		default:
			break;
		}
	}
	
	return;
}

void collectible_applyconstraints(node *this)
{	
	/* normalize angles */
	normalize_ang(this->rotation.x);
	normalize_ang(this->rotation.y);
}

void collectible_render(node *this)
{
	/* draw node */
	slPushMatrix();
		slTranslate(toFIXED(this->position.x), toFIXED(this->position.y), toFIXED(-this->position.z));
		slRotX(DEGtoANG(this->rotation.x));
		slScale(toFIXED(0.2), toFIXED(0.2), toFIXED(0.2));
		actor_render(this->node_actor);
	slPopMatrix();
	
	return;
}

void collectible_routine(node *this)
{
	switch (this->routine_index) {
		case NR_INIT:
			collectible_init(this);
			break;
		case NR_FREE:
			collectible_free(this);
			break;
		case NR_COLLIDE:
			collectible_collision(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			break;
	}
	
	return;
}
 
