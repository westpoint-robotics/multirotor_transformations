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

void OptitrackPoseToTransformStamped::setPoseStampedPublisher(ros::Publisher pose_stamped_pub) {
        pose_stamped_pub_ = pose_stamped_pub;
}

void OptitrackPoseToTransformStamped::setMarkerName(std::string name) {
        marker_name_ = name;
}

void OptitrackPoseToTransformStamped::optitrackPoseCallback(const geometry_msgs::PoseStamped &msg) {

  geometry_msgs::TransformStamped transform_stamped_msg;
  geometry_msgs::PoseStamped pose_stamped_msg;


  // Optitrack frame (ENU) to PX4 body frame (NWU) 

  transform_stamped_msg.transform.translation.x = msg.pose.position.y;
  transform_stamped_msg.transform.translation.y = -msg.pose.position.x;
  transform_stamped_msg.transform.translation.z = msg.pose.position.z;

  transform_stamped_msg.transform.rotation.x = -msg.pose.orientation.y;
  transform_stamped_msg.transform.rotation.y = msg.pose.orientation.x;
  transform_stamped_msg.transform.rotation.z = -msg.pose.orientation.z;
  transform_stamped_msg.transform.rotation.w = -msg.pose.orientation.w;

  transform_stamped_msg.header = msg.header;
  transform_stamped_pub_.publish(transform_stamped_msg);

  
  pose_stamped_msg.pose.position.x = msg.pose.position.y;
  pose_stamped_msg.pose.position.y = -msg.pose.position.x;
  pose_stamped_msg.pose.position.z = msg.pose.position.z;

  pose_stamped_msg.pose.orientation.x = -msg.pose.orientation.y;
  pose_stamped_msg.pose.orientation.y = msg.pose.orientation.x;
  pose_stamped_msg.pose.orientation.z = -msg.pose.orientation.z;
  pose_stamped_msg.pose.orientation.w = -msg.pose.orientation.w;

  pose_stamped_msg.header = msg.header;
  pose_stamped_pub_.publish(pose_stamped_msg);

  // publish tf betweee world and marker frame in the NWU frame

  transform_.setOrigin(tf::Vector3(pose_stamped_msg.pose.position.x, pose_stamped_msg.pose.position.y, pose_stamped_msg.pose.position.z));
  tf::Quaternion q(pose_stamped_msg.pose.orientation.x, pose_stamped_msg.pose.orientation.y, pose_stamped_msg.pose.orientation.z, pose_stamped_msg.pose.orientation.w);
  transform_.setRotation(q);
  tf_broadcaster_.sendTransform(tf::StampedTransform(transform_, ros::Time::now(), "world", (marker_name_ + std::string("_nwu")).c_str()));
  
}