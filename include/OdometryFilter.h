/*
 * OdometryFilter.h
 *
 *  Created on: Jun 23, 2017
 *      Author: thaus
 */

#ifndef ODOMETRYFILTER_H_
#define ODOMETRYFILTER_H_

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include <stdio.h>
#include <math.h>
#include <Eigen/Dense>


class OdometryFilter {
public:

    OdometryFilter();
    virtual ~OdometryFilter();
    void odomCallback(const nav_msgs::Odometry &msg);
    
    void setFilteredOdomPublisher(ros::Publisher publisher);
    void setFilterTimeConstant(float filter_time_constant);
    void setFilterSamplingTime(float filter_sampling_time);
    void updateFilterCoefficients();
 
 private:   
    
    ros::Publisher filtered_odom_pub_;
    Eigen::Vector3f velocity_previous_;
    float filter_time_constant_;
    float filter_coeff_u_;
    float filter_coeff_y_;
    float filter_sampling_time_;
    int last_sequence_;

};

#endif /* ODOMETRYFILTER_H_ */
