#include <ros/ros.h>

class Longitudinal_Controller {
public:
	Longitudinal_Controller();
private:
	setVelocityCommand(nav_msgs::Odometry&);
	
	//double T_d_ = 5;
	double K_p_ = 1;

	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Publisher cmd_vel_pub_;
}