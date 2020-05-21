/*
 * player - the player is you!
 */
#include "../nodes.h"

double player_move_forward;
double player_move_right;
double player_move_up;
double player_vertical_vel;
double player_vertical_accel;
bool player_has_orbit;
bool trigger_jump;

static int orbit_node;
static int orbit_child_index;

static bool standing_on_surface;

void player_init(node *this)
{
	this->node_actor = at_tet_new();
	actor_routine(this->node_actor, AR_INIT);
	
	player_has_orbit = S_FALSE;
	player_move_forward = 0.0;
	player_move_right = 0.0;
	player_move_up = 0.0;
	player_vertical_vel = 0.0;
	player_vertical_accel = -0.03;
	orbit_node = 0;
	orbit_child_index = 0;
	
	return;
}

void player_free(node *this)
{
	node_free(this);
	
	return;
}

/* 
 * TODO: tidy into a generic bounding box collision handler
 */
void player_to_box(node *player, node *box)
{
	double dist_x, dist_y, dist_z;
	double ang_x, ang_y, ang_z;
	bool box_inside_x = S_FALSE;
	bool box_inside_y = S_FALSE;
	bool box_inside_z = S_FALSE;
	bool box_collided = S_FALSE;
	bool touched_x = S_FALSE;
	bool touched_y = S_FALSE;
	bool touched_z = S_FALSE;
	
	/* detect incursion */
	if (player->position.x > box->position.x - 0.6
		&& player->position.x < box->position.x + 0.6) {
		box_inside_x = S_TRUE;
	} else
		box_inside_x = S_FALSE;

	if (player->position.y > box->position.y - 0.6
		&& player->position.y < box->position.y + 0.6) {
		box_inside_y = S_TRUE;
	} else
		box_inside_y = S_FALSE;

	if (player->position.z > box->position.z - 0.6
		&& player->position.z < box->position.z + 0.6) {
		box_inside_z = S_TRUE;
	} else
		box_inside_z = S_FALSE;

	if (box_inside_x && box_inside_y && box_inside_z)
		box_collided = S_TRUE;
	
	/* determine face of collision */
	if (box_collided) {
		dist_x = player->position_prev.x - box->position.x;
		dist_y = player->position_prev.y - box->position.y;
		dist_z = player->position_prev.z - box->position.z;
		ang_x = vecang2d_calc(dist_z, dist_y);
		if ((ang_x > 45.0 && ang_x < 135.0) 
			|| (ang_x > -135.0 && ang_x < -45.0))
		{
			if (fabs(dist_x) > fabs(dist_z))
				touched_x = S_TRUE;
			else
				touched_z = S_TRUE;
		} else {
			if (fabs(dist_x) > fabs(dist_y))
				touched_x = S_TRUE;
			else
				touched_y = S_TRUE;
		}
		box_collided = S_FALSE;
	}
	
	/* place at point of collision */
	if (touched_x) {
		if (dist_x < 0)
			player->position.x = box->position.x - 0.6;
		else
			player->position.x = box->position.x + 0.6;
	} else if (touched_y) {
		if (dist_y < 0)
			player->position.y = box->position.y - 0.6;
		else {
			player->position.y = box->position.y + 0.6;
			standing_on_surface = S_TRUE;
		}
	} else if (touched_z) {
		if (dist_z < 0)
			player->position.z = box->position.z - 0.6;
		else
			player->position.z = box->position.z + 0.6;
	}

	return;
}

void player_collision(node *this)
{
	collided has_collided = {0, 0, 0};
	unsigned short index;
	unsigned short node;
	bool got_triangle = S_FALSE;
	
	/* act on previous collisions by object type */
	for (index = 0; index < this->collisions_count; index++) {
		node = this->collisions[index].id;
		switch (graph->nodes[node]->type) {
		case NT_ENVIRONMENT:
			if (this->collisions[index].x)
				this->position.x = this->collisions[index].x * 2.9;
			if (this->collisions[index].y) {
				this->position.y = this->collisions[index].y * 2.9;			
				standing_on_surface = S_TRUE;
			}
			if (this->collisions[index].z < 0)
				this->position.z = -11.0;
			else if (this->collisions[index].z > 0)
				this->position.z = -1.1;
			break;
		default:
			break;
		}
	}
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
	node_clearcollisions(this);
	
	/* calculate collisions with stuff and notify them */
	for (index = sabs(this->id); index < graph->node_count; index++) {
		switch (graph->nodes[index]->type) {
		case NT_BOX:
				if (fabs(pointdistance3d(this->position,graph->nodes[index]->position)) > 1.0)
					break;	/* don't waste cycles calculating a box we're far away from */
				player_to_box(this, graph->nodes[index]);
				break;
		case NT_COLLECTIBLE:
			/* detect incursion */
			if ((this->position.x < graph->nodes[index]->position.x + 0.3 && this->position.x > graph->nodes[index]->position.x - 0.3)
				&& (this->position.y < graph->nodes[index]->position.y + 0.3 && this->position.y > graph->nodes[index]->position.y - 0.3)
				&& (this->position.z < graph->nodes[index]->position.z + 0.3 && this->position.z > graph->nodes[index]->position.z - 0.3)) {
				
				has_collided.x = 1;
				node_addcollision(graph->nodes[index], this, has_collided);
				got_triangle = S_TRUE;
			}
			break;
		default:
			break;
		}
		has_collided.x = 0;
		has_collided.y = 0;
		has_collided.z = 0;
	}
	
	/* act */
	if (got_triangle)
		show_triangle = S_TRUE;
	/* TODO: Above should notify of collision with boxes, but action should defer until all are calculated */
	
	return;
}

void player_addorbit(node *this)
{
	orbit_node = scene_addnode(graph, NT_ORBIT, orbit_render, orbit_routine);
	scene_positionnode(graph, orbit_node, this->position);
	scene_rotatenode(graph, orbit_node, this->rotation);
	orbit_child_index = scene_setchildnode(graph, this->id, orbit_node);

	return;
}

void player_processinput(node *this)
{
	/* motion */
	if (input_mask & IM_UP) player_move_forward += motion_constant;
	if (input_mask & IM_DOWN) player_move_forward -= motion_constant;
	if (input_mask & IM_LEFT) player_move_right -= motion_constant;
	if (input_mask & IM_RIGHT) player_move_right += motion_constant;
	if ((input_mask & IM_ACTION1) && standing_on_surface) {player_vertical_vel = 0.35; standing_on_surface = S_FALSE;}
	if (input_mask & IM_ACTION2) player_has_orbit = S_TRUE;
	
	if (player_has_orbit && orbit_node == 0) {
		player_addorbit(this);
	}
	
	input_mask = 0;
	
	return;
}

void player_applyconstraints(node *this)
{
	unsigned int child;
	vect_component orbit_comps = { 0.0, 0.0 };
	vect_component camera_xz = { 0.0, 0.0 };
	
	/* determine current x normal */ 
	veccomp2d_calc(1.0, graph->camera->rotation.x, &camera_xz);
	
	/* move based on velocity */
	/* motion relative to camera angle */
	if (player_move_forward) {
		this->position.x += player_move_forward * camera_xz.y;
		this->position.z += player_move_forward * camera_xz.x;
		if (player_move_forward > 0.0)
			this->rotation.x = -graph->camera->rotation.x;
		else
			this->rotation.x = 540 - graph->camera->rotation.x;
		player_move_forward = 0.0;
	}
	if (player_move_right) {
		if (this->position.z > graph->camera->position.z) {
			veccomp2d_calc(player_move_right, graph->camera->rotation.x, &camera_xz);
			this->position.x += camera_xz.x;
			this->position.z -= camera_xz.y;
		} else {
			veccomp2d_calc(-player_move_right, graph->camera->rotation.x, &camera_xz);
			this->position.x -= camera_xz.x;
			this->position.z += camera_xz.y;
		}
		if (player_move_right > 0.0)
			this->rotation.x = -graph->camera->rotation.x - 90.0;
		else
			this->rotation.x = -graph->camera->rotation.x + 90.0;
		player_move_right = 0.0;
	}
	
	/* handle children */
	if (this->children_count > 0 && this->children != NULL) {
		for (child = 0; child < this->children_count; child++) {
			switch (this->children[child]->type) {
			case NT_ORBIT:
				veccomp2d_calc(0.2, -this->rotation.x, &orbit_comps);
				this->children[child]->position.x = this->position.x - orbit_comps.y;
				this->children[child]->position.y = this->position.y;
				this->children[child]->position.z = this->position.z - orbit_comps.x;
				node_routine(this->children[child], NR_ORBIT_CONSTRAINT);
				break;
			default:
				break;
			}
		}
	}
	
	/* vertical accel and velocity */
	player_vertical_vel += player_vertical_accel;
	this->position.y += player_vertical_vel;
	
	if (standing_on_surface)
		player_vertical_vel = 0.0;
	
	/* normalize angles */
	normalize_ang(this->rotation.x);
	normalize_ang(this->rotation.y);
	
	/* clear standing flag until detected again */
	standing_on_surface = S_FALSE;
	
	return;
}

void player_render(node *this)
{
	/* draw node */
	slPushMatrix();
		slTranslate(toFIXED(this->position.x), toFIXED(this->position.y), toFIXED(-this->position.z));
		slRotX(DEGtoANG(this->rotation.x));
		slScale(toFIXED(0.1), toFIXED(0.1), toFIXED(0.1));
		actor_render(this->node_actor);
	slPopMatrix();
	
	/* retain previous position for vector calcs */
	this->position_prev.x = this->position.x;
	this->position_prev.y = this->position.y;
	this->position_prev.z = this->position.z;
	
	return;
}

void player_routine(node *this)
{
	switch (this->routine_index) {
		case NR_INIT:
			player_init(this);
			break;
		case NR_FREE:
			player_free(this);
			break;
		case NR_COLLIDE:
			player_collision(this);
			break;
		case NR_PLAYER_INPUT:
			player_processinput(this);
			break;
		case NR_PLAYER_CONSTRAINT:
			player_applyconstraints(this);
			break;
		default: /* NR_INIT | NR_FREE if not case'd above */
			break;
	}
	
	return;
}
