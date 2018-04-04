#ifndef _HELPER_FUNCTIONS_
#define _HELPER_FUNCTIONS_
#include <cmath>
#include <XmlRpcValue.h>

double distanceToDestination(double curr_x, double curr_y, double dest_x, double dest_y){
	return sqrt(pow(dest_x - curr_x, 2.0) + pow(dest_y - curr_y, 2.0));
}

// std::vector< double > makeArrayFromRosParamList(std::vector<double>  my_list){
// 	std::vector< double > destinations;
// 	for (int i = 0; i < my_list.size(); i++){
// 		destinations.push_back(static_cast<double>(my_list[i]));
// 	}
// 	return destinations;
// }

#endif