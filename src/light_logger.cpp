#include <ros/ros.h>
#include <rosserial_arduino/Adc.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <rosaria/BumperState.h>
#include <iomanip> // for std :: setprecision and std :: fixed
#include <yaw_controller.h>
#include <cmath>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include "tf/transform_datatypes.h"
#include <stdio.h>
#include <helper_functions.h>
#include <math.h>
#include <light_logger.h>
// XmlRpc::XmlRpcValue my_list;
// #include <tf/LinearMath/Matrix3x3.h>
using namespace std;

Light_Logger::Light_Logger() {
	nh_.param<double>("sampling_distance", sampling_distance_, 0.01);
	pose_sub_ = nh_.subscribe("RosAria/pose", 1, &Light_Logger::logLightIfOverSamplingDistance_cb, this);
	adc_sub_ = nh_.subscribe("/adc", 1, &Light_Logger::updateLightSample_cb, this);
	// cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("yaw_controller/cmd_vel", 1);
	numOfEntriesLogged_pub_ = nh_.advertise<std_msgs::Float64>("lightEntriesLogged", 1);
	recievedFirstLightSample_ = false;
	loggedOneSample_ = false;
}

void Light_Logger::updateLightSample_cb(const rosserial_arduino::Adc::ConstPtr msg){
	if (!recievedFirstLightSample_){
		recievedFirstLightSample_ = true;
	}
	lightSample_ = (double)msg->adc0;
}

void Light_Logger::logLightIfOverSamplingDistance_cb(const nav_msgs::Odometry::ConstPtr msg){
	pos_x_ = msg->pose.pose.position.x;
	pos_y_ = msg->pose.pose.position.y;
	if (recievedFirstLightSample_){
		if (lightLog.size()){
			double lastLog_x_ = lightLog.back().x;
			double lastLog_y_ = lightLog.back().y;
			if (distanceBetweenTwoPoints(pos_x_, pos_y_, lastLog_x_, lastLog_y_ ) > sampling_distance_){
				ROS_WARN("lastLog_x_: %f", lastLog_x_);
				ROS_WARN("lastLog_y_: %f", lastLog_y_);
				ROS_WARN("lightLog.size(): %f", lightLog.size());				
				// lightLogEntry entry(pos_x_, pos_y_, lightSample_, ros::Time::now().toSec());
				lightLogEntry entry;
				entry.x = pos_x_;
				entry.y = pos_y_;
				entry.lightIntensity = lightSample_;
				entry.timestamp = ros::Time::now().toSec();
				lightLog.push_back(entry);
				lightEntriesLogged_++;
				ROS_WARN("New entry logged");
			}
		}else {
			lightLogEntry entry;
			entry.x = pos_x_;
			entry.y = pos_y_;
			entry.lightIntensity = lightSample_;
			entry.timestamp = ros::Time::now().toSec();
			// lightLogEntry entry(pos_x_, pos_y_, lightSample_, ros::Time::now().toSec());
			lightLog.push_back(entry);
			lightEntriesLogged_++;
			loggedOneSample_ = true;
		}
	}
}

Light_Logger::~Light_Logger() {
	cout << "Shutting down Light_Logger" << endl;
	double numOfLoggEntries = lightLog.size();
	cout << "Number of logged entries: " << numOfLoggEntries << endl;	
}



int main(int argc, char **argv)
{
	// Initialize the ROS system and become a node.
	ros::init(argc, argv, "light_logger");

	Light_Logger light_logger;

	ros::Rate r(50);
	
	while (ros::ok()) {
		ros::spinOnce();
		r.sleep();
	}
}
