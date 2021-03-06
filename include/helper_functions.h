#ifndef _HELPER_FUNCTIONS_
#define _HELPER_FUNCTIONS_
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <XmlRpcValue.h>
#include "light_log_entry.h"

using namespace std;

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


bool saveLogToFile(std::vector<lightLogEntry> lightLog)
{
	string const HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";
	stringstream ss;
	ss << HOME << "/catkin_ws/src/rosaria_client/scripts/data/lightLog.csv";
	string s = ss.str();

	ofstream myfile;

	char tab2[1024];
	strcpy(tab2, s.c_str());

	myfile.open(tab2);
	myfile << "x,y,light_intensity,timestamp \n";

	// (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)

	for (std::vector<lightLogEntry>::iterator iter = lightLog.begin(); iter != lightLog.end(); iter++ ){
		myfile << iter->x << "," << iter->y << "," << iter->lightIntensity << "," << iter->timestamp << endl;
	}

	myfile.close();
  	return true;
}



#endif