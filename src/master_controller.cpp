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
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include "tf/transform_datatypes.h"
#include <stdio.h>
#include "helper_functions.h"
// #include <tf/LinearMath/Matrix3x3.h>
using namespace std;

Master_Controller::Master_Controller() {
	nh_.param<double>("reached_destination_margin", reached_destination_margin_, 0.3);
	nh_.getParam("destinations", destinations);
	pose_sub_ = nh_.subscribe("RosAria/pose", 1, &Master_Controller::checkIfReachedDestination_cb, this);
	coordinate_pub_ = nh_.advertise<geometry_msgs::Pose2D>("setDestinationCoordinates", 1);
	setpoint_pos_x = destinations[0];
	setpoint_pos_y = destinations[1];
	publishNextDestination();
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
	double distToDest = distanceBetweenTwoPoints(current_pos_x, current_pos_y, setpoint_pos_x, setpoint_pos_y);

	if (distToDest < reached_destination_margin_){
		destinations.erase(destinations.begin());
		destinations.erase(destinations.begin());
		if (destinations.size() >= 2){
			setpoint_pos_x = destinations[0];
			setpoint_pos_y = destinations[1];
			publishNextDestination();
		}
	}

}


int main(int argc, char **argv)
{
	// Initialize the ROS system and become a node.
	ros::init(argc, argv, "master_controller");

	Master_Controller master_controller;

	ros::Rate r(10);
	
	while (ros::ok()) {
		ros::spinOnce();
		master_controller.publishNextDestination();
		r.sleep();
	}
}
