/*
 * prim - primitive related objects and functions
 */
#ifndef __PRIM_H__
#define __PRIM_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* coordinates */
#include "coord.h"

/* 2d primitives */
typedef struct poly2d {
    unsigned char point_count;
    point2d *points;
} poly2d;
typedef poly2d tri2d;
typedef poly2d quad2d;

/* 2d primitives init */
poly2d *new_poly2d(unsigned char point_count, ...);

/* 3d primitives */
typedef struct poly3d {
    unsigned char point_count;
    point3d *points;
} poly3d;
typedef poly3d tri3d;
typedef poly3d quad3d;

/* 3d primitives init */
poly3d *new_poly3d(unsigned char point_count, ...);
void draw_tri3d(tri3d *poly, unsigned char r, unsigned char g, unsigned char b);
void draw_quad3d(quad3d *poly, unsigned char r, unsigned char g, unsigned char b);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __PRIM_H__ */
