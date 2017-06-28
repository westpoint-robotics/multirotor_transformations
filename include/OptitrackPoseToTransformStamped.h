/*
 * OptitrackPoseToTransformStamped.h
 *
 *  Created on: Jun 22, 2017
 *      Author: thaus
 */

#ifndef OPTITRACKPOSETOTRANSFORMSTAMPED_H_
#define OPTITRACKPOSETOTRANSFORMSTAMPED_H_

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TransformStamped.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <math.h>


class OptitrackPoseToTransformStamped {
public:

    OptitrackPoseToTransformStamped();
    virtual ~OptitrackPoseToTransformStamped();
    void optitrackPoseCallback(const geometry_msgs::PoseStamped &msg);
    
    void setTransformStampedPublisher(ros::Publisher publisher);
    void setPoseStampedPublisher(ros::Publisher publisher);
 
 private:   
    
    ros::Publisher transform_stamped_pub_;
    ros::Publisher pose_stamped_pub_;
};

#endif /* OPTITRACKPOSETOTRANSFORMSTAMPED_H_ */
