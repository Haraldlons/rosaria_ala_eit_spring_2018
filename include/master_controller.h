#include <ros/ros.h>

class Master_Controller {
private:

	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Publisher coordinate_pub_;
	double reached_destination_margin_;
	double setpoint_pos_x = 1000;
	double setpoint_pos_y = 1000;
	std::vector<double> destinations;
	void checkIfReachedDestination_cb(nav_msgs::Odometry::ConstPtr);
	

	double yaw_cmd_vel_;
	double linear_cmd_vel_;
	void getLinearCommand_cb(geometry_msgs::Twist::ConstPtr);
	void publishMotorCommand();

public:
	void publishNextDestination();
	Master_Controller();
};