/*
 * actor_test - a test of scene graphs
 */
#include "actor_test.h"
#include "actor_test_obj/nodes.h"			

/* scene */
scene *graph;

/* some global constants */
double motion_constant;
double gravity_constant;
double scale_constant;

/* wrapper input to mode input */
int input_mask;

/* trigger to display triangle in HUD */
bool show_triangle;
								  
static double bounding_box[] = {-2.9, 2.9, -2.9, 2.9, -11.0, -1.1};
static float fog_color[] = { 0.3f, 0.3f, 0.3f, 1.0f };
static point3d node_positions[] = {{0.0,0.0,0.0},{0.0,0.0,-2.0},{0.0,0.0,-5.0},{0.0,-2.5,-6.0},{0.0,-1.5,-7.0},{0.0,-0.5,-8.0},{0.0,-0.5,-11.0},{0.0,1.5,-11.0}};
static point3d node_angles[] = {{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0}};

/*
 * actor_test_init - OpenGL init
 */
bool actor_test_init(void)
{
	signed short box_1, box_2, box_3, box_4, a_collectible;
	
	/* --- scene init --- */
	
	input_mask = 0;
	motion_constant = 0.1;		/* constants for our world */
	gravity_constant = -0.09;	/* TODO: make meta-data of the environment node */
	scale_constant = 0.1;
	show_triangle = S_FALSE;

	/* create graph */
	graph = scene_new();
	
	/* scene projection */
	scene_projection_new(graph, PROJECTION_FRUSTUM, scale_constant * current_ratio, scale_constant, scale_constant, 50.0);

	/* setup collision bounding box */
	graph->bounding_box[0] = bounding_box[0];
	graph->bounding_box[1] = bounding_box[1];
	graph->bounding_box[2] = bounding_box[2];
	graph->bounding_box[3] = bounding_box[3];
	graph->bounding_box[4] = bounding_box[4];
	graph->bounding_box[5] = bounding_box[5];
	
	/* create node collection */
	
	/* create node 00 - environment */
	environment_node = scene_addnode(graph, NT_ENVIRONMENT, environment_render, environment_routine);
	scene_positionnode(graph, environment_node, node_positions[environment_node]);
	scene_rotatenode(graph, environment_node, node_angles[environment_node]);

	/* create node 01 - camera */
	camera_node = scene_addnode(graph, NT_CAMERA, NULL, NULL);
	scene_positionnode(graph, camera_node, node_positions[camera_node]);
	scene_rotatenode(graph, camera_node, node_angles[camera_node]);
	scene_setchildnode(graph, environment_node, camera_node);
		
	/* create node 02 - player box */
	player_node = scene_addnode(graph, NT_PLAYER, player_render, player_routine);
	scene_positionnode(graph, player_node, node_positions[player_node]);
	scene_rotatenode(graph, player_node, node_angles[player_node]);
	scene_setchildnode(graph, environment_node, player_node);
	
	/* create node 03 - 05 - some boxes to jump on */
	box_1 = scene_addnode(graph, NT_BOX, box_render, box_routine);
	box_2 = scene_addnode(graph, NT_BOX, box_render, box_routine);
	box_3 = scene_addnode(graph, NT_BOX, box_render, box_routine);
	scene_positionnode(graph, box_1, node_positions[box_1]);
	scene_positionnode(graph, box_2, node_positions[box_2]);
	scene_positionnode(graph, box_3, node_positions[box_3]);
	scene_rotatenode(graph, box_1, node_angles[box_1]);
	scene_rotatenode(graph, box_2, node_angles[box_2]);
	scene_rotatenode(graph, box_3, node_angles[box_3]);
	scene_setchildnode(graph, environment_node, box_1);
	scene_setchildnode(graph, environment_node, box_2);
	scene_setchildnode(graph, environment_node, box_3);
	
	/* create note 06 - a box to put a collectible on */
	box_4 = scene_addnode(graph, NT_BOX, box_render, box_routine);
	scene_positionnode(graph, box_4, node_positions[box_4]);
	scene_rotatenode(graph, box_4, node_angles[box_4]);
	scene_setchildnode(graph, environment_node, box_4);
	
	
	/* create node 07 - a collectible triangle! */
	a_collectible = scene_addnode(graph, NT_COLLECTIBLE, collectible_render, collectible_routine);
	scene_positionnode(graph, a_collectible, node_positions[a_collectible]);
	scene_rotatenode(graph, a_collectible, node_angles[a_collectible]);
	scene_setchildnode(graph, environment_node, a_collectible);
	
	/* assign environment */
	graph->environment = graph->nodes[environment_node];
	
	/* assign camera */
	graph->camera = graph->nodes[camera_node];
	
	/* assign player */
	graph->player = graph->nodes[player_node];
	
	/* assign environment as our root node */
	graph->root_node = graph->environment;

	/* --- OpenGL Init ---
	
	/* TODO: Create OpenGL "modes" that control all parameter switching
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_FOG);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* color settings
	glClearColor(fog_color[0], fog_color[1], fog_color[2], fog_color[3]);
	glShadeModel(GL_SMOOTH);
	
	/* setup culling
	glCullFace(GL_BACK);
	
	/* fog setup
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_DENSITY, 0.45f);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 10.0f);
	
	/* setup projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	*/

	switch(graph->prj_type) {
	case PROJECTION_ORTHAGONAL:
		/*glOrtho(graph->prj[0], graph->prj[1], graph->prj[2], graph->prj[3], graph->prj[4], graph->prj[5]);*/
		break;
	case PROJECTION_FRUSTUM:
		slPerspective(DEGtoANG(90.0));
		slZdspLevel(2);
		break;
	default:
		return S_FALSE;
		break;
	}
	
	return S_TRUE;
}

/*
 * actor_test_render - OpenGL rendering
 */
bool actor_test_render(void)
{
	unsigned int node_index;
	
	/* projection matrix */
	slPushMatrix();
		/* begin rendering in world space */
		slPushMatrix();
		
			/* perform camera transformation */
			camera_refresh(graph->camera);
		
			/* step through nodes render functions */
			for (node_index = 0; node_index < graph->node_count; node_index++) {
				node_render(graph->nodes[node_index]);
			}
		
		/* end rendering in world space */
		slPopMatrix();
	slPopMatrix();
	
	/* TODO: draw this on a VDP2 scroll plane above VDP1 layer */
	/* if (show_triangle) {
		glDisable(GL_DEPTH_TEST);

		glBegin(GL_TRIANGLES);
			glColor4d(1.0, 1.0, 0.0, 0.0);
			glVertex3d(-0.75, -0.5, -1.0);
			glVertex3d(-0.95, -0.95, -1.0);
			glVertex3d(-0.55, -0.95, -1.0);
		glEnd();

		glEnable(GL_DEPTH_TEST);
	} */
	
	/* flush */
	slSynch();
	
	return S_TRUE;
}

/*
 * actor_test_input - handle movement
 */
bool actor_test_input(void)
{	
	/* TODO: Handle controller feedback */

	return S_TRUE;
}

/*
 * actor_test_routine -  process object routine 
 */
bool actor_test_routine(void)
{
	/* handle the player's input and apply constraints to result */
	node_routine(graph->player, NR_PLAYER_INPUT);
	node_routine(graph->player, NR_PLAYER_CONSTRAINT);
	
	/* process the collision state of the scene */
	node_routine(graph->root_node, NR_COLLIDE);

	/* enforce camera that follows the player */
	/* camera is always after the player */
	camera_routine(graph->camera, graph->player);
	
	return S_TRUE;
}

/*
 * actor_test_free - OpenGL free
 */
bool actor_test_free(void)
{
	scene_free(graph);
	
	return S_TRUE;
}

