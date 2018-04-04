#include <ros/ros.h>

class Motor_Controller {
private:

	ros::NodeHandle nh_;
	ros::Subscriber yaw_sub_;
	ros::Subscriber longitudinal_sub_;
	ros::Publisher cmd_vel_pub_;
	

	void setMotorCommand(nav_msgs::Odometry::ConstPtr);
	
	double yaw_cmd_vel_;
	double linear_cmd_vel_;
	void getYawCommand_cb(geometry_msgs::Twist::ConstPtr);
	void getLinearCommand_cb(geometry_msgs::Twist::ConstPtr);
	void publishMotorCommand();

public:
	Motor_Controller();
};