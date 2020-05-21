/*
 * veccomp - vector components
 */
#include "../../util/macros.h"
#include "vect.h"

/*
 * veccomp2d_calc - calculate the components of a 2D vector with given magnitude and angle
 */
void veccomp2d_calc(double magnitude, double angle, vect_component *new)
{	
	
	new->x = magnitude * f_double(MTH_Cos(toFIXED(degtorad(angle)))); /* FIXED-TO-DOUBLE */
	new->y = magnitude * f_double(MTH_Sin(toFIXED(degtorad(angle)))); /* FIXED-TO-DOUBLE */
		
	return;
}

/*
 * vecang2d_calc - calculate the angle from normal for a displacement using arctangent
 */
double vecang2d_calc(double x_comp, double y_comp)
{
	double angle;
	
	/* some easily defined values */
	if (y_comp == 0) {
		if (x_comp > 0)
			return 90.0;
		else if (x_comp < 0)
			return -90.0;
		else
			return 0.0;
	}
	
	if (x_comp == 0 && y_comp < 0)
		return 180.0;
	
	/* calculate value */
	angle = radtodeg(f_double(MTH_Atan(toFIXED(y_comp), toFIXED(x_comp)))); /* FIXED-TO-DOUBLE */
	
	/* negative y values do strange things */
	if (y_comp < 0) {
		if (x_comp > 0) {
			angle += 180.0;
		} else {
			angle -= 180.0;
		}
	}
	
	return angle;
}
