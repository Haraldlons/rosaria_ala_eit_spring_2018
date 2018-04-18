#ifndef _HELPER_FUNCTIONS_
#define _HELPER_FUNCTIONS_
#include <cmath>
#include <XmlRpcValue.h>

double distanceBetweenTwoPoints(double curr_x, double curr_y, double dest_x, double dest_y){
	return sqrt(pow(dest_x - curr_x, 2.0) + pow(dest_y - curr_y, 2.0));
}


double findSmallestYawError(double setpoint, double current_yaw){
	double yaw_error = setpoint - current_yaw;
	if (yaw_error > M_PI){
		yaw_error = yaw_error - 2*M_PI;
	}else if(yaw_error < -M_PI){
		yaw_error = yaw_error + 2*M_PI;
	}
	if(yaw_error < -M_PI/2){
		yaw_error = yaw_error + M_PI;
	}else if(yaw_error > M_PI/2){
		yaw_error = yaw_error - M_PI;
	}
	return yaw_error;
}

#endif