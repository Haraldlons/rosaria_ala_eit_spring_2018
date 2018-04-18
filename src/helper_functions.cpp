#include "rosaria_client/include/helper_functions.h"
// #include <math.h>
#include <cmath>

double distanceBetweenTwoPoints(double curr_x, double curr_y, double dest_x, double dest_y){
	return sqrt(pow(dest_x - curr_x, 2.0) + pow(dest_y - curr_y, 2.0));
}