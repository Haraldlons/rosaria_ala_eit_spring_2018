#include <ros/ros.h>

class Motor_Controller {
public:
	Motor_Controller();
private:

	double integral_ = 0;
	double T_i_ = 5;
	double K_p_ = 6;
	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Publisher cmd_vel_pub_;
	ros::Publisher yaw_;
	void setSteeringCommand(nav_msgs::Odometry::ConstPtr);
};