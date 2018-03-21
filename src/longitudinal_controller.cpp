#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <iomanip>
#include <longitudinal_controller.h>
#include <cmath>
#include "tf/transform_datatypes.h"
#include<geometry_msgs/Twist.h>
using namespace std;

Longitudinal_Controller::Motor_Controller() {
	pose_sub_ = nh_.subscribe("RosAria/pose", 1, &setVelocityCommand);
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 1);
}



void Longitudinal_Controller::setVelocityCommand(const nav_msgs::Odometry& msg){
	//const double pi == 3.14159;
	double current_pos_x = msg.pose.pose.position.x; double current_pos_y = msg.pose.pose.position.y;
	double current_yaw = tf::getYaw(msg->pose.pose.orientation);
	double setpoint_pos_x = 1; double setpoint_pos_y = 1;
	double angle_to_point = atan2(setpoint_pos_x - current_pos_y, setpoint_pos_y - current_pos_x)
	double abs_pos_error = sqrt(pow(setpoint_pos_x - current_pos_x, 2.0) + pow(setpoint_pos_y - current_pos_y, 2.0));
	double theta = angle_to_point - current_yaw;
	double pos_error = abs_pos_error*cos(theta);
	double longit_vel_cmd = K_p_*pos_error;
	geometry_msgs::Twist twist;
	twist.linear.x = longit_vel_cmd;
	cmd_vel_pub_.publish(twist);
}

int main(int argc, char **argv)
{
	// Initialize the ROS system and become a node.
	ros::init(argc, argv, "longitudinal_controller");

	Motor_Controller controller_object;

	ros::Rate r(10);
	
	while (ros::ok()) {
		ros::spinOnce();
		r.sleep();
	}
}
