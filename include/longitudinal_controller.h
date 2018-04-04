#include <ros/ros.h>
#include<geometry_msgs/Pose2D.h>

class Longitudinal_Controller {
private:

	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Subscriber dest_sub_;
	ros::Publisher cmd_vel_pub_;

	void setVelocityCommand(nav_msgs::Odometry::ConstPtr);
	void getDestinationCoordinates(geometry_msgs::Pose2D::ConstPtr);
	//double T_d_ = 5;
	double K_p_;
	double setpoint_pos_x;
	double setpoint_pos_y;

public:
	Longitudinal_Controller();
};