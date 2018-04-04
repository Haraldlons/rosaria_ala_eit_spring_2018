#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>

class Yaw_Controller {
public:
	Yaw_Controller();
private:

	double T_i_ = 5.0;
	double K_p_ = 0.8;
	double setpoint = 0.0;
	double setpoint_pos_x = 0.0;
	double setpoint_pos_y = 0.0;

	double regulator_min_radius_;
	
	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Subscriber dest_sub_;
	
	ros::Publisher cmd_vel_pub_;
	ros::Publisher yaw_;
	void setSteeringCommand(nav_msgs::Odometry::ConstPtr);
	void getDestinationCoordinates(geometry_msgs::Pose2D::ConstPtr);
	// double distanceToDestination(double, double);
};