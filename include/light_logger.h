#include <ros/ros.h>

struct lightLogEntry
{
	double x;
	double y;
	double lightIntensity;
	double timestamp;
	lightLogEntry(double x, double y,double lightIntensity,double timestamp){
		x = x;
		y = y;
		lightIntensity = lightIntensity;
		timestamp = timestamp;
	};
};

class Light_Logger {
private:

	ros::NodeHandle nh_;
	ros::Subscriber pose_sub_;
	ros::Subscriber adc_sub_;
	ros::Publisher numOfEntriesLogged_pub_;

	double sampling_distance_;

	bool recievedFirstLightSample_;
	bool loggedOneSample_;
	double last_light_sample_;
	double pos_x_;
	double pos_y_;
	double lightSample_;
	double lightEntriesLogged_;
	std::vector<lightLogEntry> lightLog;
	
	void logLightIfOverSamplingDistance_cb(geometry_msgs::Pose2D::ConstPtr);
	void updateLightSample_cb(rosserial_arduino::Adc::ConstPtr);


public:
	void publishNextDestination();
	Light_Logger();
	~Light_Logger();
};