#include <ros/ros.h>

class Master_Controller {
private:

	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Publisher coordinate_pub_;
	double[] destinations;
	void checkIfReachedDestination_cb(nav_msgs::Odometry::ConstPtr);
	void publishNextDestination();
	

	double yaw_cmd_vel_;
	double linear_cmd_vel_;
	void getLinearCommand_cb(geometry_msgs::Twist::ConstPtr);
	void publishMotorCommand();

public:
	Master_Controller();
};