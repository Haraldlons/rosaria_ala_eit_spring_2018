#include "helper_functions.h"
#include <XmlRpcValue.h> 
#include <gtest/gtest.h>

TEST(TestHelperFunctions, distanceToDestination_0_difference){
	double returnValue = distanceToDestination(0.0, 0.0, 0.0, 0.0);
	double expectedValue = 0;
	EXPECT_EQ(expectedValue, returnValue);
}

TEST(TestHelperFunctions, makeArrayFromRosParamList_simple_list){
	XmlRpc::XmlRpcValue my_list(2.0);
	// my_list.push_back(2.0);
	std::vector< double > returnValue = makeArrayFromRosParamList(my_list);
	EXPECT_EQ(1, returnValue.size());
}


int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}