/*
 * node - a single node in a scene graph
 */
#include "node.h"

/*
 * new - generates a new node with initialized values
 */
node *node_new(signed short id, signed int type, void (*render)(node *this), void (*routine)(node *this))
{
	node *new_node = (node *) MEM_Malloc(sizeof (node));	/* TODO: We are getting stuck here...why */
		new_node->id = id;
		new_node->type = type;
		new_node->node_actor = NULL;
		new_node->children = NULL;
		new_node->children_count = 0;
		new_node->collisions = NULL;
		new_node->collisions_count = 0;
		new_node->render = render;
		new_node->routine = routine;
		new_node->world_bind = S_TRUE;
		new_node->position.x = 0.0;
		new_node->position.y = 0.0;
		new_node->position.z = 0.0;
		new_node->rotation.x = 0.0;
		new_node->rotation.y = 0.0;
		new_node->rotation.z = 0.0;
	
	return new_node;
}

/*
 * addcollision - add a record of a collision with *collided
 * 
 *  the node maintains an active, dynamic collection of collisions as they are happening
 *  the collision indicates which node in the graph collided 
 *  a collision is only added if it actually exists, a zero collision is discarded
 */
void node_addcollision(node *this, node *colliding_node, collided has_collided)
{
	if (has_collided.x != 0 || has_collided.y != 0 || has_collided.z != 0) {
		collided *new_collisions = (collided *) MEM_Realloc(this->collisions, ++this->collisions_count * sizeof (collided));
		this->collisions = new_collisions;
		this->collisions[this->collisions_count - 1].id = colliding_node->id;
		this->collisions[this->collisions_count - 1].x = has_collided.x;
		this->collisions[this->collisions_count - 1].y = has_collided.y;
		this->collisions[this->collisions_count - 1].z = has_collided.z;
	}
	
	return;
}

/*
 * clearcollisions - clear all collisions
 * 
 *  ideal to call after fully processing collisions but before processing ones
 *  own collisions, as the collision collection may be used to process objects further down the tree as well
 */
void node_clearcollisions(node *this)
{
	MEM_Free(this->collisions);
	this->collisions = NULL;
	this->collisions_count = 0;
	
	return;
}

/*
 * render - render the node
 * 
 * 	the render routine is responsible for calling
 * 	the render routine of the actor
 */
void node_render(node *this)
{
	if (this != NULL && this->render != NULL && this->id >= 0)
		this->render(this);
	
	return;
}

/*
 * routine - process the node
 * 
 * 	the node is responsible for calling routines
 * 	on the actor
 */
void node_routine(node *this, signed char routine_index)
{

	if (this != NULL
			&& this->routine != NULL
			&& this->id >= 0
			&& routine_index != NR_NULL) {
		this->routine_index = routine_index;
		this->routine(this);
	}
	
	return;
}

/*
 * free - free up memory used by the node
 * 
 *  triggers a free on the actor if defined
 *  frees the children collection, then frees
 *  the node itself
 */
void node_free(node *this)
{
	if (this != NULL) {
		if (this->node_actor != NULL)
			actor_routine(this->node_actor, AR_FREE);
		if (this->children != NULL)
			MEM_Free(this->children);
		MEM_Free(this);
	}
	
	return;
}

/* addchildnode - add one node to the child collection of another
 * 
 * expands and inserts a node into the child collection of an existing node
 * 
 * unlike nodes in the scene, a child node does not have an id, simply a position
 * in the index, as it is just a pointer to the node in question
 * a node is responsible for managing its children, but this will hand it
 * an index if it asks nicely
 */
unsigned short node_addchildnode(node *this, node *child)
{
	node **children = (node **) MEM_Realloc(this->children, ++this->children_count * sizeof (node *));
	this->children = children;
	this->children[this->children_count - 1] = child;
	
	return this->children_count - 1;
}

/*
 * prunechildnode - remove a child node from a collection
 * 
 * carefully removes a child node from the collection at
 * the given index
 */
void node_prunechildnode(node *this, unsigned short index)
{
	unsigned short child;
	short newpos = 0;
	node **pruned_children = (node **) MEM_Malloc((this->children_count - 1) * sizeof (node *));
	
	for (child = 0; child < this->children_count; child++) {
		if (child == index)
			continue;
		pruned_children[newpos++] = this->children[child];
	}
	
	MEM_Free(this->children);
	this->children = pruned_children;
	this->children_count--;
	
	return;
}
