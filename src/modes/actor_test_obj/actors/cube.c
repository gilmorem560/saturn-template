/*
 * cube - a normaler than average cube
 */ 
#include "../actors.h"

/* at_cube - a normaler than average cube */
static POINT at_cube_point[] = {
		POStoFIXED(-1.0, 1.0, 1.0)
		,POStoFIXED(-1.0, -1.0, 1.0)
		,POStoFIXED(1.0, -1.0, 1.0)
		,POStoFIXED(1.0, 1.0, 1.0)
		,POStoFIXED(1.0, 1.0, -1.0)
		,POStoFIXED(1.0, -1.0, -1.0)
		,POStoFIXED(-1.0, -1.0, -1.0)
		,POStoFIXED(-1.0,  1.0, -1.0)
};

static POLYGON at_cube_poly[] = {
		NORMAL(0.0, 0.0, 1.0), VERTICES(0, 1, 2, 3)
		,NORMAL(1.0, 0.0, 0.0), VERTICES(3, 2, 5, 4)
		,NORMAL(0.0, 0.0, -1.0), VERTICES(4, 5, 6, 7)
		,NORMAL(-1.0, 0.0, 0.0), VERTICES(7, 6, 1, 0)
		,NORMAL(0.0, 1.0, 0.0), VERTICES(7, 0, 3, 4)
		,NORMAL(0.0, -1.0, 0.0), VERTICES(1, 6, 5, 2)
};

static ATTR at_cube_attr[] = {
		ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(255, 0, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(0, 255, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(0, 0, 255), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(255, 255, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(0, 255, 255), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(255, 0, 255), No_Gouraud, MESHoff, sprPolygon, No_Option)
};

static PDATA at_cube_pdata = {
		at_cube_point, sizeof (at_cube_point) / sizeof (POINT)
		,at_cube_poly, sizeof (at_cube_poly) / sizeof (POLYGON)
		,at_cube_attr
};

actor *at_cube_new(void)
{
	actor *new_actor = actor_new_actor(AT_CUBE, at_cube_render, at_cube_routine);
	
	return new_actor;
}

/* 00 - init */
void at_cube_init(actor *this)
{
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_cube_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_cube_render - render the cube itself
 */
void at_cube_render(actor *this)
{
	slPushMatrix();
		slPutPolygon(&at_cube_pdata);
	slPopMatrix();

	return;
}

/*
 * at_cube_routine - handle routing to various routines
 */
void at_cube_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_cube_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_cube_free(this);
		break;
	default:
		break;
	}
	
	return;
}
