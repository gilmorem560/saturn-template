/*
 * poly3d - basic polygon in 3d space
 */
#include <stdarg.h>

#include <sgl.h>

#include "coord.h"  /* coordinate objects */
#include "prim.h"   /* primitive shapes */

/*
 * new_poly3d - create a new polygon from an indeterminate number of points
 */
poly3d *new_poly3d(unsigned char point_count, ...)
{
    va_list points;
    poly3d *newpoly = NULL;

    /* need more than two points for a polygon */
    if (point_count >= 3) {
        newpoly = (poly3d *) MEM_Calloc(1, sizeof (poly3d));
        if (newpoly != NULL) {
            newpoly->point_count = point_count;
            newpoly->points = (point3d *) MEM_Calloc(point_count, sizeof (point3d));
            if (newpoly->points != NULL) {
                va_start(points, point_count);
                do {
                    newpoly->points[point_count - 1] = va_arg(points, point3d);
                } while (point_count-- > 1);
            }
        }
    }

    va_end(points);

    return newpoly;
}

/*
 * draw_tri3d - draw a triangle
 */
void draw_tri3d(tri3d *poly, unsigned char r, unsigned char g, unsigned char b)
{
    int a;
    POINT vertices[3];
    POLYGON my_poly[] = {
    	NORMAL(0.0, 0.0, 1.0), VERTICES(0, 0, 1, 2)
    };
    ATTR faceAttributes[] = {
    		ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(r, g, b), No_Gouraud, MESHoff, sprPolygon, No_Option)
    };
    PDATA drawData = {
    		vertices, sizeof (vertices) / sizeof (POINT)
			,my_poly, sizeof (my_poly) / sizeof (POLYGON)
			,faceAttributes
    };

    for (a = 0; a < 3; a++) {
    	vertices[a][X] = toFIXED(poly->points[a].x);
    	vertices[a][Y] = toFIXED(poly->points[a].y);
    	vertices[a][Z] = toFIXED(poly->points[a].z);
    }

    slPutPolygon(&drawData);
    
    return;
}

/*
 * draw_quad3d - draw a quad
 */
void draw_quad3d(quad3d *poly, unsigned char r, unsigned char g, unsigned char b)
{
    int a;
    POINT vertices[4];
    POLYGON my_poly[] = {
    	NORMAL(0.0, 0.0, 1.0), VERTICES(0, 1, 2, 3)
    };
    ATTR faceAttributes[] = {
    		ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, C_RGB(r, g, b), No_Gouraud, MESHoff, sprPolygon, No_Option)
    };
    PDATA drawData = {
    		vertices, sizeof (vertices) / sizeof (POINT)
			,my_poly, sizeof (my_poly) / sizeof (POLYGON)
			,faceAttributes
    };

    for (a = 0; a < 4; a++) {
    	vertices[a][X] = toFIXED(poly->points[a].x);
    	vertices[a][Y] = toFIXED(poly->points[a].y);
    	vertices[a][Z] = toFIXED(poly->points[a].z);
    }

    slPutPolygon(&drawData);
    
    return;
}

