/*
 * Px4ImuTransform.h
 *
 *  Created on: Jun 23, 2017
 *      Author: thaus
 */

#ifndef PX4IMUTRANSFORM_H_
#define PX4IMUTRANSFORM_H_

#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include <stdio.h>
#include <math.h>


class Px4ImuTransform {
public:

    Px4ImuTransform();
    virtual ~Px4ImuTransform();
    void imuCallback(const sensor_msgs::Imu &msg);
    
    void setTransformedImuPublisher(ros::Publisher publisher);
 
 private:   
    
    ros::Publisher transformed_imu_pub_;
};

#endif /* PX4IMUTRANSFORM_H_ */
