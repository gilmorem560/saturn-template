/*
 * macros - useful macros
 */
#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
#ifndef M_PI
#define M_PI	3.14159265358979323846264
#endif /* M_PI */

#include <sgl.h>
#include <sega_mem.h>
#include <sega_mth.h>
#define f_double(a) ((double)((a) / 65536.0))

#define	degtorad(deg)		(deg / 360.0) * 2.0 * M_PI
#define radtodeg(rad)		(rad * 180.0) / M_PI
#define dotprod2d(a,b)		a.x*b.x + a.y*b.y
#define dotprod3d(a,b)		a.x*b.x + a.y*b.y + a.z*b.z
#define hypotenuse(a,b)		f_double(MTH_Sqrt(toFIXED(a*a + b*b))) /* FIXED-TO-DOUBLE */

/* boolean types */
typedef char bool;
#define	S_TRUE	1
#define	S_FALSE 0

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MACROS_H__ */
