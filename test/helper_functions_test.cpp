#include "helper_functions.h"
#include <gtest/gtest.h>

TEST(TestHelperFunctions, distanceToDestination){
	double expectedValue = 2;
	EXPECT_EQ(expectedValue, 2);
}


int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}