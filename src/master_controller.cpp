#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <rosaria/BumperState.h>
#include <iomanip> // for std :: setprecision and std :: fixed
#include <master_controller.h>
#include <cmath>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include "tf/transform_datatypes.h"
#include <stdio.h>

// #include <tf/LinearMath/Matrix3x3.h>
using namespace std;

Master_Controller::Master_Controller() {
	nh_.param<double>("reached_destination_margin", reached_destination_margin_, 0.3);
	pose_sub_ = nh_.subscribe("RosAria/pose", 1, &Master_Controller::checkIfReachedDestination_cb, this);
	coordinate_pub_ = nh_.advertise<geometry_msgs::Pose2D>("setDestinationCoordinates", 1);
	
}

double Master_Controller::distanceToDestination(double current_pos_x, double current_pos_y, double setpoint_pos_x, double setpoint_pos_y){
	return sqrt(pow(setpoint_pos_x - current_pos_x, 2.0) + pow(setpoint_pos_y - current_pos_y, 2.0));
}

void Master_Controller::publishNextDestination(){
	geometry_msgs::Pose2D pose2d;
	pose2d.x = destinations[0];
	pose2d.y = destinations[1];
	coordinate_pub_.publish(pose2d);
}

void Master_Controller::checkIfReachedDestination_cb(const nav_msgs::Odometry::ConstPtr msg){
	double current_pos_x = msg->pose.pose.position.x;
	double current_pos_y = msg->pose.pose.position.y;
	double setpoint_pos_x = destinations[0];
	double setpoint_pos_y = destinations[1];
	double distanceToDestination = distanceToDestination(current_pos_x, current_pos_y, setpoint_pos_x, setpoint_pos_y);

}

double Yaw_Controller::distanceToDestination(double current_pos_x, double current_pos_y){
	return sqrt(pow(setpoint_pos_x - current_pos_x, 2.0) + pow(setpoint_pos_y - current_pos_y, 2.0));
}

void Yaw_Controller::setSteeringCommand(const nav_msgs::Odometry::ConstPtr msg){
	double current_pos_x = msg->pose.pose.position.x;
	double current_pos_y = msg->pose.pose.position.y;

	double setpoint = atan2(setpoint_pos_y-current_pos_y, setpoint_pos_x-current_pos_x);
	double current_yaw = tf::getYaw(msg->pose.pose.orientation);
	double yaw_error;
	double distToDest = distanceToDestination(current_pos_x, current_pos_y);
	if ( distToDest < regulator_min_radius_){
		yaw_error = 0;
	}else{
		yaw_error = setpoint - current_yaw;
	}

	double yaw_vel_cmd = K_p_*yaw_error;
	geometry_msgs::Twist twist;
	twist.angular.z = yaw_vel_cmd;
	cmd_vel_pub_.publish(twist);

	std_msgs::Float32 theta32;
	theta32.data = static_cast<float>(current_yaw);

	// std_msgs::Float32 yaw = (std_msgs::Float32) current_yaw;
	yaw_.publish(theta32);
}

int main(int argc, char **argv)
{
	// Initialize the ROS system and become a node.
	ros::init(argc, argv, "yaw_controller");

	Yaw_Controller controller_object;

	ros::Rate r(10);
	
	while (ros::ok()) {
		ros::spinOnce();
		r.sleep();
	}
}
