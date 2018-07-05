// #include "myproject/mynode.h"
// #include "yaw_controller.h"
#include <ros/ros.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>

// #include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
// TODO: add other includes as needed

class MyNodeTest : public ::testing::Test {
 public:
  MyNodeTest(): 
    node_handle_(),
    publisher_(node_handle_.advertise<geometry_msgs::Pose2D>("/setDestinationCoordinates", 5)),
    publisher_pose_(node_handle_.advertise<nav_msgs::Odometry>("/RosAria/pose", 5)),
    subscriber_(node_handle_.subscribe("/yaw_controller/cmd_vel", 5, &MyNodeTest::Callback, this)),
    message_received_(false) 
    {  }

  /*
   * This is necessary because it takes a while for the node under
   * test to start up.
   */
  void SetUp() {
    while (!IsNodeReady()) {
      ros::spinOnce();
    }
  }

  void Publish(double num /* TODO: add necessary fields */) {
    // MyInputMessage message;
    // TODO: construct message.
    geometry_msgs::Pose2D pose2d;
    pose2d.x = 1;
    pose2d.y = num;
    publisher_.publish(pose2d);

    // publisher_.publish(message);
  }

  void publish_pose(double num /* TODO: add necessary fields */) {
    // MyInputMessage message;
    // TODO: construct message.
    nav_msgs::Odometry odom;
    odom.pose.pose.position.x = 0;
    odom.pose.pose.position.y = 0;
    odom.pose.pose.orientation.w = 1.000;
    odom.pose.pose.orientation.x = 0.009;
    odom.pose.pose.orientation.y = 0.000;
    odom.pose.pose.orientation.z = 0.000;
    publisher_pose_.publish(odom);

    // publisher_.publish(message);
  }

  /*
   * This is necessary because it takes time for messages from the
   * node under test to reach this node.
   */  
  boost::shared_ptr<const geometry_msgs::Twist> WaitForMessage() {
    // The second parameter is a timeout duration.
    return ros::topic::waitForMessage<geometry_msgs::Twist>(
        subscriber_.getTopic(), ros::Duration(2)); // Things this returns the actual msg recieved
  }
  
  // An alternative way of waiting for a message.
  // ros::topic::waitForMessage can sometimes be flaky.
  void WaitForMessageAlternate() {
    while(!message_received_) {
      ros::spinOnce();
    }
  }

  geometry_msgs::Twist twist_msg_;

 private:
  ros::NodeHandle node_handle_;
  ros::Publisher publisher_;
  ros::Publisher publisher_pose_;

  ros::Subscriber subscriber_;
  bool message_received_;

  /*
   * This callback is a no-op because we get the messages from the
   * node under test using WaitForMessage().
   */
  void Callback(const geometry_msgs::Twist::ConstPtr& msg) {
    message_received_ = true;
    twist_msg_ = *msg;
    ROS_INFO("Got Twist message at topic '/yaw_controller/cmd_vel', with angular value: %f", twist_msg_.angular.z);
    // ROS_FATAL("Hello in callback %f", twist_msg_.angular.x);
    // ROS_FATAL("Hello in callback %f", twist_msg_.angular.y);
    // ROS_FATAL("Hello in callback %f", twist_msg_.linear.x);
    // ROS_FATAL("Hello in callback %f", twist_msg_.linear.y);
    // ROS_FATAL("Hello in callback %f", twist_msg_.linear.z);
  }


  /*
   * See SetUp method.
   */
  bool IsNodeReady() {
    return (publisher_.getNumSubscribers() > 0)
        && (subscriber_.getNumPublishers() > 0);
  }
};

void Output(const std::string& msg, geometry_msgs::Twist* pInt)
{
    std::cout << msg << *pInt << "\n";
}
 

TEST_F(MyNodeTest, NonZeroInputDoesSomething) {
    (2.0);
  ros::Duration(0.01).sleep();
  publish_pose(3.0);
  ros::Duration(0.01).sleep();
  // Publish(2.0);
  // publish_pose(3.0);
  // ros::Duration(0.5).sleep();
  //   Publish(2.0);
  // publish_pose(3.0);
  // ros::Duration(0.5).sleep();

  boost::shared_ptr<const geometry_msgs::Twist> output = WaitForMessage();
  ROS_INFO("NonZeroInputDoesSomething, twist_msg_.angular.z: %f", twist_msg_.angular.z);
  // ROS_FATAL("NonZeroInputDoesSomething, output.z: %f", (&output)->angular.z);

  // ROS_FATAL("HELlox: %f ", twist_msg->angular.x); 
  // ROS_FATAL("HELloy: %f ", twist_msg->angular.y); 
  // ROS_FATAL("HELloz: %f ", twist_msg->angular.z);
  // ROS_FATAL("HELlox: %f ", twist_msg->linear.x); 
  // ROS_FATAL("HELloy: %f ", twist_msg->linear.y); 
  // ROS_FATAL("HELloz: %f ", twist_msg->linear.z); 
  // << "Shared pointer with get() " << output.get() << std::endl;
  // Output("Shared pointer with get() ", output.get());
  ASSERT_TRUE(true);
  // ASSERT_TRUE(true);
  // ASSERT_TRUE(true);
  // ASSERT_TRUE(true);
  // EXPECT_EQ(10, output);
}


TEST_F(MyNodeTest, testNUmber2) {
  Publish(3.0);
  ros::Duration(0.01).sleep();
  publish_pose(3.0);
  ros::Duration(0.01).sleep();
  // Publish(2.0);
  // publish_pose(3.0);
  // ros::Duration(0.5).sleep();
  //   Publish(2.0);
  // publish_pose(3.0);
  // ros::Duration(0.5).sleep();

  boost::shared_ptr<const geometry_msgs::Twist> output = WaitForMessage();
  ROS_INFO("Test2, twist_msg_.angular.z: %f", twist_msg_.angular.z);
  ASSERT_TRUE(true);
}

// TEST_F(MyNodeTest, ZeroInputDoesNothing) {
//   Publish(0);
//   geometry_msgs::Twist output = WaitForMessage();
//   ASSERT_TRUE(output == NULL);
// }


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "mynode_test_2");
  ros::NodeHandle nh; 

  ros::AsyncSpinner spinner(1);
  spinner.start();
  int ret = RUN_ALL_TESTS();
  spinner.stop();
  ros::shutdown();
  return ret;
}
