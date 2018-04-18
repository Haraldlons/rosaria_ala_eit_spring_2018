#include "helper_functions.h"
#include <gtest/gtest.h>
#include <math.h>
#include <light_log_entry.h>
// #include <nav_msgs/Odometry.h>
// #include <geometry_msgs/Twist.h>
// #include <geometry_msgs/Pose2D.h>
// #include <light_logger.h>

TEST(TestHelperFunctions, distanceBetweenTwoPoints_0_difference){
	double returnValue = distanceBetweenTwoPoints(0.0, 0.0, 0.0, 0.0);
	double expectedValue = 0;
	EXPECT_EQ(expectedValue, returnValue);
}

TEST(TestHelperFunctions, distanceBetweenTwoPoints_5_difference){
	double returnValue = distanceBetweenTwoPoints(0.0, 0.0, 3.0, 4.0);
	double expectedValue = 5;
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

TEST(TestHelperFunctions, saveLogToFile_simple){
	std::vector<lightLogEntry> lightLog;
	for (int i = 0; i < 10; i++){
		lightLogEntry entry;
		entry.x = i;
		entry.y = i;
		entry.lightIntensity = i*i;
		entry.timestamp = i;
		lightLog.push_back(entry);
	}
	EXPECT_TRUE(saveLogToFile(lightLog));
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