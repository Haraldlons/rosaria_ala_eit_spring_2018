#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <rosaria/BumperState.h>
#include <iomanip> // for std :: setprecision and std :: fixed
#include <motor_controller.h>
#include <cmath>
#include<geometry_msgs/Twist.h>
using namespace std;

Motor_Controller::Motor_Controller() {
	pose_sub_ = nh_.subscribe("RosAria/pose", 1, &setSteeringCommand);
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 1);
}


void Motor_Controller::setSteeringCommand(const nav_msgs::Odometry& msg){
	double current_yaw = msg.pose.pose.orientation.w;
	double setpoint = 2.8;
	double yaw_error = setpoint - current_yaw;
	integral += yaw_error/(10*T_i_);
	double yaw_vel_cmd = K_p_*yaw_error + integral;
	geometry_msgs::Twist twist;
	twist.angular.z = yaw_vel_cmd;
	cmd_vel_pub_.publish(twist);
}

int main(int argc, char **argv)
{
	// Initialize the ROS system and become a node.
	ros::init(argc, argv, "motor_controller");

	Motor_Controller controller_object;

	ros::Rate r(10);
	
	while (ros::ok()) {
		ros::spinOnce();
		r.sleep();
	}
}
