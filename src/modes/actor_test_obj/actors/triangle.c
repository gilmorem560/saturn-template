/*
 * triangle - a normaler than average triangle
 */ 
#include "../actors.h"

/* at_triangle - a normaler than average triangle */
static POINT at_triangle_point[] = {
		POStoFIXED(0.0, 1.0, 0.0)
		,POStoFIXED(-1.0, -1.0, 0.0)
		,POStoFIXED(1.0, -1.0, 0.0)
};

static POLYGON at_triangle_poly[] = {
		NORMAL(0.0, 0.0, 1.0), VERTICES(0, 0, 1, 2)
};

static ATTR at_triangle_attr[] = {
		ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(255, 255, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
};

static PDATA at_triangle_pdata = {
		at_triangle_point, sizeof (at_triangle_point) / sizeof (POINT)
		,at_triangle_poly, sizeof (at_triangle_poly) / sizeof (POLYGON)
		,at_triangle_attr
};

actor *at_triangle_new(void)
{
	actor *new_actor = actor_new_actor(AT_TRIANGLE, at_triangle_render, at_triangle_routine);
	
	return new_actor;
}

/* 00 - init */
void at_triangle_init(actor *this)
{
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_triangle_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_triangle_render - render the triangle itself
 */
void at_triangle_render(actor *this)
{
	slPushMatrix();
		slPutPolygon(&at_triangle_pdata);
	slPopMatrix();

	return;
}

/*
 * at_triangle_routine - handle routing to various routines
 */
void at_triangle_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_triangle_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_triangle_free(this);
		break;
	default:
		break;
	}
	
	return;
}
