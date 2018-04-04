// #include "myproject/mynode.h"
// #include "yaw_controller.h"
#include <ros/ros.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
// TODO: add other includes as needed

class MyNodeTest : public ::testing::Test {
 public:
  MyNodeTest()
      : node_handle_(),
        publisher_(
            node_handle_.advertise<geometry_msgs::Pose2D>(
                "/setDestinationCoordinates", 5)),
        publisher_pose_(node_handle_.advertise<nav_msgs::Odometry>(
                "/RosAria/pose", 5)),
        subscriber_(
            node_handle_.subscribe("/yaw_controller/cmd_vel", 5,
                                   &MyNodeTest::Callback,
                                   this)),
        message_received_(false) {
  }

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
    pose2d.x = 5;
    pose2d.y = num;
    publisher_.publish(pose2d);

    // publisher_.publish(message);
  }

  void publish_pose(double num /* TODO: add necessary fields */) {
    // MyInputMessage message;
    // TODO: construct message.
    nav_msgs::Odometry odom;
    odom.pose.pose.position.x = 0;
    odom.pose.pose.position.y = num;
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
        subscriber_.getTopic(), ros::Duration(2));
  }
  
  // An alternative way of waiting for a message.
  // ros::topic::waitForMessage can sometimes be flaky.
  void WaitForMessageAlternate() {
    while(!message_received_) {
      ros::spinOnce();
    }
  }

  geometry_msgs::Twist::ConstPtr twist_msg;
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
  void Callback(const geometry_msgs::Twist::ConstPtr event) {
    message_received_ = true;
    twist_msg = event;
    ROS_FATAL("HELloy %s", twist_msg->angular.z);
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
  Publish(6.0);
  publish_pose(3.0);
  boost::shared_ptr<const geometry_msgs::Twist> output = WaitForMessage();
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

// TEST_F(MyNodeTest, ZeroInputDoesNothing) {
//   Publish(0);
//   geometry_msgs::Twist output = WaitForMessage();
//   ASSERT_TRUE(output == NULL);
// }


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "mynode_test_2");

  ros::AsyncSpinner spinner(1);
  spinner.start();
  int ret = RUN_ALL_TESTS();
  spinner.stop();
  ros::shutdown();
  return ret;
}
