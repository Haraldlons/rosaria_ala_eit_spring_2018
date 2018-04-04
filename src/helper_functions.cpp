#include "helper_functions.h"
// #include <math.h>
#include <cmath>

double distanceToDestination(double current_pos_x, double current_pos_y){
	return sqrt(pow(setpoint_pos_x - current_pos_x, 2.0) + pow(setpoint_pos_y - current_pos_y, 2.0));
}