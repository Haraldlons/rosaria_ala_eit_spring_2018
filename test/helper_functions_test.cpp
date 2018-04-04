#include "helper_functions.h"
#include <gtest/gtest.h>
#include <math.h>

TEST(TestHelperFunctions, distanceToDestination_0_difference){
	double returnValue = distanceToDestination(0.0, 0.0, 0.0, 0.0);
	double expectedValue = 0;
	EXPECT_EQ(expectedValue, returnValue);
}

TEST(TestHelperFunctions, findSmallestYawError_0_error){
	double setpoint = 0;
	double current_yaw = 0;
	double returnValue = findSmallestYawError(setpoint, current_yaw);
	EXPECT_EQ(0, returnValue);
}

TEST(TestHelperFunctions, findSmallestYawError_pi_half_error){
	double setpoint = M_PI/2;
	double current_yaw = 0;
	double returnValue = findSmallestYawError(setpoint, current_yaw);
	double expectedValue = M_PI/2;
	EXPECT_EQ(expectedValue, returnValue);
}

TEST(TestHelperFunctions, findSmallestYawError_turn_left){
	double setpoint = M_PI-0.1;
	double current_yaw = -0.20;
	double returnValue = findSmallestYawError(setpoint, current_yaw);
	double expectedValue = 0.10;
	EXPECT_TRUE(fabs(expectedValue - returnValue) < 0.01);
}

TEST(TestHelperFunctions, findSmallestYawError_turn_slightly_right){
	double setpoint = -M_PI+0.1;
	double current_yaw = 0.20;
	double returnValue = findSmallestYawError(setpoint, current_yaw);
	double expectedValue = -0.10;
	EXPECT_TRUE(fabs(expectedValue - returnValue) < 0.01);
}



int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// TEST(TestHelperFunctions, function_name_test_case){
// 	argument_1 = 
// 	argument_2 = 
// 	dataType returnValue = function_name(argument_1, argument_2);
// 	dataType expectedValue = 
// 	EXPECT_EQ(expectedValue, returnValue)
// }