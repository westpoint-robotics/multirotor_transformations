/*
 * OptitrackPoseToTransformStamped.cpp
 *
 *  Created on: Jun 22, 2017
 *      Author: thaus
 */


#include "OptitrackPoseToTransformStamped.h"

OptitrackPoseToTransformStamped::OptitrackPoseToTransformStamped() {
    // TODO Auto-generated constructor stub
}

OptitrackPoseToTransformStamped::~OptitrackPoseToTransformStamped() {
	// TODO Auto-generated destructor stub
}

void OptitrackPoseToTransformStamped::setTransformStampedPublisher(ros::Publisher transform_stamped_pub) {
        transform_stamped_pub_ = transform_stamped_pub;
}


void OptitrackPoseToTransformStamped::optitrackPoseCallback(const geometry_msgs::PoseStamped &msg) {

  geometry_msgs::TransformStamped transform_stamped_msg;

  // Optitrack frame (ENU) to PX4 body frame (NED) 

  transform_stamped_msg.transform.translation.x = msg.pose.position.y;
  transform_stamped_msg.transform.translation.y = msg.pose.position.x;
  transform_stamped_msg.transform.translation.z = -msg.pose.position.z;

  transform_stamped_msg.transform.rotation.x = msg.pose.orientation.y;
  transform_stamped_msg.transform.rotation.y = msg.pose.orientation.x;
  transform_stamped_msg.transform.rotation.z = -msg.pose.orientation.z;
  transform_stamped_msg.transform.rotation.w = msg.pose.orientation.w;

  transform_stamped_msg.header = msg.header;
  transform_stamped_pub_.publish(transform_stamped_msg);

}