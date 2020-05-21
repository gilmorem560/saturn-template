/*
 * tetrahedron - a normaler than average tetrahedron
 */ 
#include "../actors.h"

/* at_triangle - a normaler than average triangle */
static POINT at_tet_point[] = {
		POStoFIXED(0.0, -1.0, -1.0)
		,POStoFIXED(1.0, -1.0, 1.0)
		,POStoFIXED(-1.0, -1.0, 1.0)
		,POStoFIXED(0.0, 1.0, 0.0)
};

static POLYGON at_tet_poly[] = {
		NORMAL(0.0, -1.0, 0.0), VERTICES(0, 0, 1, 2)
		,NORMAL(-1.0, 0.5, 1.0), VERTICES(0, 0, 3, 1)
		,NORMAL(1.0, 0.5, 1.0), VERTICES(0, 0, 2, 3)
		,NORMAL(0.0, 0.5, -1.0), VERTICES(3, 3, 2, 1)
};

static ATTR at_tet_attr[] = {
		ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(255, 0, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(0, 255, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(0, 0, 255), No_Gouraud, MESHoff, sprPolygon, No_Option)
		,ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(255, 255, 0), No_Gouraud, MESHoff, sprPolygon, No_Option)
};

static PDATA at_tet_pdata = {
		at_tet_point, sizeof (at_tet_point) / sizeof (POINT)
		,at_tet_poly, sizeof (at_tet_poly) / sizeof (POLYGON)
		,at_tet_attr
};

actor *at_tet_new(void)
{
	actor *new_actor = actor_new_actor(AT_TETRAHEDRON, at_tet_render, at_tet_routine);
	
	return new_actor;
}

/* 00 - init */
void at_tet_init(actor *this)
{
	/* setup routine */
	this->routine_index = AR_NULL;
	
	return;
}

/* 01 - free */
void at_tet_free(actor *this)
{
	actor_free(this);
	
	return;
}

/*
 * at_tet_render - render the tetrahedron itself
 */
void at_tet_render(actor *this)
{
	slPushMatrix();
		slPutPolygon(&at_tet_pdata);
	slPopMatrix();

	return;
}

/*
 * at_tet_routine - handle routing to various routines
 */
void at_tet_routine(actor *this)
{
	switch (this->routine_index) {
	case AR_NULL:	/* -1 */
		break;
	case AR_INIT:	/* 0 */
		at_tet_init(this);
		break;
	case AR_FREE:	/* 1 */
		at_tet_free(this);
		break;
	default:
		break;
	}
	
	return;
}
