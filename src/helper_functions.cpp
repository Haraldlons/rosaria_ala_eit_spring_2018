#include "rosaria_client/include/helper_functions.h"
// #include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <lightEntryLog.h>

double distanceBetweenTwoPoints(double curr_x, double curr_y, double dest_x, double dest_y){
	return sqrt(pow(dest_x - curr_x, 2.0) + pow(dest_y - curr_y, 2.0));
}


// bool saveLogToFile(std::vector<lightLogEntry> lightLog)
// {
//       ofstream myfile;
//       myfile.open ("lightLog.csv");
//       myfile << "x, y, light_intensity, timestamp \n";

//       // (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)

//       for (auto iter = lightLog.begin(); iter != lightLog.end(); iter++ ){
//       	myfile << iter.x << ", " << iter.y << ", " << iter.lightIntensity << ", " << iter.timestamp << endl;
//       }

//       myfile.close();
//       return true;
// }