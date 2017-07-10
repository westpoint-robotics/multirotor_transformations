/*
 * MarkerOptitrack.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: thaus
 */


#include "MarkerOptitrack.h"

MarkerOptitrack::MarkerOptitrack() :
  new_uav_pose_received_(false),
  new_marker_pose_received_(false)
{
    // TODO Auto-generated constructor stub
}

MarkerOptitrack::~MarkerOptitrack() {
	// TODO Auto-generated destructor stub
}

void MarkerOptitrack::setUavRelativePosePublisher(ros::Publisher publisher) {
        uav_relative_pose_pub_ = publisher;
}


void MarkerOptitrack::uavPoseCallback(const geometry_msgs::PoseStamped &msg) {
    
    uav_pose.pose.position.x = msg.pose.position.y;
    uav_pose.pose.position.y = -msg.pose.position.x;
    uav_pose.pose.position.z = msg.pose.position.z;

    uav_pose.pose.orientation.x = -msg.pose.orientation.y;
    uav_pose.pose.orientation.y = msg.pose.orientation.x;
    uav_pose.pose.orientation.z = -msg.pose.orientation.z;
    uav_pose.pose.orientation.w = -msg.pose.orientation.w;

    uav_pose.header = msg.header;

    new_uav_pose_received_ = true; 
    //ROS_INFO("Uav pose callback"); 
}

void MarkerOptitrack::markerPoseCallback(const geometry_msgs::PoseStamped &msg) {

    marker_pose.pose.position.x = msg.pose.position.y;
    marker_pose.pose.position.y = -msg.pose.position.x;
    marker_pose.pose.position.z = msg.pose.position.z;

    marker_pose.pose.orientation.x = -msg.pose.orientation.y;
    marker_pose.pose.orientation.y = msg.pose.orientation.x;
    marker_pose.pose.orientation.z = -msg.pose.orientation.z;
    marker_pose.pose.orientation.w = -msg.pose.orientation.w;

    marker_pose.header = msg.header;

    new_marker_pose_received_ = true;
    //ROS_INFO("Marker pose callback");
}

bool MarkerOptitrack::isNewUavPoseReceived() {
  return new_uav_pose_received_;
}

bool MarkerOptitrack::isNewMarkerPoseReceived() {
  return new_marker_pose_received_;
}

void MarkerOptitrack::clearNewUavPoseFlag() {
  new_uav_pose_received_ = false;
}

void MarkerOptitrack::clearNewMarkerPoseFlag() {
  new_marker_pose_received_ = false;
}

void MarkerOptitrack::publishUavRelativePose(geometry_msgs::PoseStamped msg) {
  uav_relative_pose_pub_.publish(msg);

}