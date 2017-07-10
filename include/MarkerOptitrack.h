/*
 * MarkerOptitrack.h
 *
 *  Created on: Jul 5, 2017
 *      Author: thaus
 */

#ifndef MARKEROPTITRACK_H_
#define MARKEROPTITRACK_H_
	
#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TransformStamped.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <eigen3/Eigen/Eigen>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <math.h>


class MarkerOptitrack {
public:

    MarkerOptitrack();
    virtual ~MarkerOptitrack();
    void uavPoseCallback(const geometry_msgs::PoseStamped &msg);
    void markerPoseCallback(const geometry_msgs::PoseStamped &msg);
    void setUavRelativePosePublisher(ros::Publisher publisher);
    void publishUavRelativePose(geometry_msgs::PoseStamped msg);
    bool isNewUavPoseReceived();
    bool isNewMarkerPoseReceived();
    void clearNewUavPoseFlag();
    void clearNewMarkerPoseFlag();
    geometry_msgs::PoseStamped uav_pose;
    geometry_msgs::PoseStamped marker_pose;
 
 private:   
    
    ros::Publisher uav_relative_pose_pub_;
   
    bool new_uav_pose_received_;
    bool new_marker_pose_received_;
};

#endif /* MARKEROPTITRACK_H_ */
