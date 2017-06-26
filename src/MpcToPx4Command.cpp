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


void MpcToPx4Command::mpcCmdCallback(const mav_msgs::RollPitchYawrateThrust &msg) {

  std_msgs::Float64 thrust_msg;
  geometry_msgs::PoseStamped attitude_msg;

  // from the thrust message just use z component and scale to 0-1
  thrust_msg.data = msg.thrust.z / thrust_max_;

  // neglect yaw rate and transform roll, pitch , yaw(0) to quaternion
  tf::Quaternion quaternion;
  quaternion.setEulerZYX(0, msg.pitch, msg.roll);

  attitude_msg.header = msg.header;
  attitude_msg.pose.orientation.x  = quaternion.x();
  attitude_msg.pose.orientation.y  = quaternion.y();
  attitude_msg.pose.orientation.z  = quaternion.z();
  attitude_msg.pose.orientation.w  = quaternion.w();

  px4_thrust_cmd_pub_.publish(thrust_msg);
  px4_attitude_cmd_pub_.publish(attitude_msg);

}