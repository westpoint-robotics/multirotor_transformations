/*
 * MpcToPx4Command.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: thaus
 */


#include "MpcToPx4Command.h"

MpcToPx4Command::MpcToPx4Command():
  thrust_max_(25)
{
    // TODO Auto-generated constructor stub
}

MpcToPx4Command::~MpcToPx4Command() {
	// TODO Auto-generated destructor stub
}

void MpcToPx4Command::setPx4AttitudeCmdPublisher(ros::Publisher attitude_cmd_pub) {
  px4_attitude_cmd_pub_ = attitude_cmd_pub;
}

void MpcToPx4Command::setPx4ThrustCmdPublisher(ros::Publisher thrust_cmd_pub) {
  px4_thrust_cmd_pub_ = thrust_cmd_pub;
}

void MpcToPx4Command::setPx4AngularVelCmdPublisher(ros::Publisher angular_vel_cmd_pub) {
  px4_angular_vel_cmd_pub_ = angular_vel_cmd_pub;
}

void MpcToPx4Command::setMaxThrust(float thrust_max) {
  thrust_max_ = thrust_max;
}


void MpcToPx4Command::mpcCmdCallback(const mav_msgs::RollPitchYawrateThrust &msg) {

  std_msgs::Float64 thrust_msg;
  geometry_msgs::PoseStamped attitude_msg;
  geometry_msgs::TwistStamped twist_msg;

  // from the thrust message just use z component and scale to 0-1
  thrust_msg.data = msg.thrust.z / thrust_max_;
  if (thrust_msg.data > 1.0) {
    thrust_msg.data = 1.0;
  }
  else if (thrust_msg.data < 0.0) {
    thrust_msg.data = 0.0;
  }

  //transform roll, pitch , yaw to quaternion
  // to ensure bumpless transfer between different modes for yaw use measured yaw (from imu)
  tf::Quaternion quaternion;
  tf::Matrix3x3 m;
  m.setEulerYPR(yaw_imu_, msg.pitch, msg.roll);
  m.getRotation(quaternion);

  //quaternion.setEulerZYX(yaw_imu_, msg.pitch, msg.roll);

  attitude_msg.header = msg.header;
  attitude_msg.pose.orientation.x  = quaternion.x();
  attitude_msg.pose.orientation.y  = quaternion.y();
  attitude_msg.pose.orientation.z  = quaternion.z();
  attitude_msg.pose.orientation.w  = quaternion.w();

  twist_msg.header = msg.header;
  twist_msg.twist.linear.x = 0;
  twist_msg.twist.linear.y = 0;
  twist_msg.twist.linear.z = 0;

  twist_msg.twist.angular.x = 0;
  twist_msg.twist.angular.y = 0;
  twist_msg.twist.angular.z = -msg.yaw_rate;

  px4_thrust_cmd_pub_.publish(thrust_msg);
  px4_attitude_cmd_pub_.publish(attitude_msg);
  px4_angular_vel_cmd_pub_.publish(twist_msg);

}

void MpcToPx4Command::imuCallback(const sensor_msgs::Imu &msg) {

  double roll, pitch, yaw;
  // transform quaternion to euler
  tf::Quaternion quaternion_imu(msg.orientation.x, msg.orientation.y, msg.orientation.z, msg.orientation.w);
  tf::Matrix3x3 m(quaternion_imu);
  m.getEulerYPR(yaw, pitch, roll);
  yaw_imu_ = yaw;

}
