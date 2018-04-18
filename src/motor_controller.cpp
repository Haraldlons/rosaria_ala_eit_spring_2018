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
#include "tf/transform_datatypes.h"
#include <std_msgs/Float32.h>
#include <stdio.h>

// This is just for testing purposes

// #include <tf/LinearMath/Matrix3x3.h>
using namespace std;

Motor_Controller::Motor_Controller() {
	yaw_sub_ = nh_.subscribe("yaw_controller/cmd_vel", 1, &Motor_Controller::getYawCommand_cb, this);
	longitudinal_sub_ = nh_.subscribe("long_controller/cmd_vel", 1, &Motor_Controller::getLinearCommand_cb, this);

	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 1);
}

void Motor_Controller::getYawCommand_cb(const geometry_msgs::Twist::ConstPtr msg){
	yaw_cmd_vel_ = msg->angular.z;
  	ROS_INFO("yaw_cmd_vel_: %f", yaw_cmd_vel_);
	publishMotorCommand();
}

void Motor_Controller::getLinearCommand_cb(const geometry_msgs::Twist::ConstPtr msg){
	linear_cmd_vel_ = msg->linear.x;
  	ROS_INFO("linear_cmd_vel_: %f", linear_cmd_vel_);
	publishMotorCommand();
}

void Motor_Controller::publishMotorCommand(){
	geometry_msgs::Twist twist;
	twist.angular.z = yaw_cmd_vel_;
	twist.linear.x = linear_cmd_vel_;
	cmd_vel_pub_.publish(twist);
}


int main(int argc, char **argv)
{
	// Initialize the ROS system and become a node.
	ros::init(argc, argv, "motor_controller");

	Motor_Controller motor_object;

	ros::Rate r(10);

	while (ros::ok()) {
		ros::spinOnce();
		r.sleep();
	}
}
