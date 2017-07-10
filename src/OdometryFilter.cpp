/*
 * OdometryFilter.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: thaus
 */


#include "OdometryFilter.h"

OdometryFilter::OdometryFilter():
  filter_time_constant_(0.0),
  filter_sampling_time_(0.01),
  filter_coeff_u_(1.0),
  filter_coeff_y_(0.0),
  last_sequence_(-1)
{
  velocity_previous_(0) = 0.0;
  velocity_previous_(1) = 0.0;
  velocity_previous_(2) = 0.0;
}

OdometryFilter::~OdometryFilter() {
	// TODO Auto-generated destructor stub
}

void OdometryFilter::setFilteredOdomPublisher(ros::Publisher publisher) {
  filtered_odom_pub_ = publisher;
}

void OdometryFilter::setFilterTimeConstant(float filter_time_constant) {
  filter_time_constant_ = filter_time_constant;
}

void OdometryFilter::setFilterSamplingTime(float filter_sampling_time) {
  filter_sampling_time_ = filter_sampling_time;
} 

void OdometryFilter::updateFilterCoefficients() {
  // compute filter coefficients
  filter_coeff_y_ = filter_time_constant_ / (filter_time_constant_ + filter_sampling_time_);
  // filter gain could be parameter, but it should be set to 1.0 in order not to scale measurements
  filter_coeff_u_ = 1.0 * filter_sampling_time_ / (filter_time_constant_ + filter_sampling_time_);
}


void OdometryFilter::odomCallback(const nav_msgs::Odometry &msg) {

  nav_msgs::Odometry odom_msg;
  Eigen::Vector3f velocity;
 
  odom_msg = msg;

  if (last_sequence_ == -1) {
    // first message
    last_sequence_ = msg.header.seq;
  }
  else {
    if (msg.header.seq != (last_sequence_  + 1)) 
      ROS_INFO("Lost some messages, expected seq %d, got seq %d", last_sequence_  + 1, msg.header.seq);
  }

  last_sequence_ = msg.header.seq;

  // filter linear velocities
  // simple PT1 filter is used:
  // vel(k) = a * y(k-1) + b * u(k)
  // coefficients a = filter_coeff_y_, coefficient b = filter_coeff_u_ are computed in updateFilterCoefficients
  
  velocity(0) = msg.twist.twist.linear.x;
  velocity(1) = msg.twist.twist.linear.y;
  velocity(2) = msg.twist.twist.linear.z;

  velocity = filter_coeff_y_ * velocity_previous_ + filter_coeff_u_ * velocity;

  odom_msg.twist.twist.linear.x = velocity(0);
  odom_msg.twist.twist.linear.y = velocity(1);
  odom_msg.twist.twist.linear.z = velocity(2);

  velocity_previous_ = velocity;

  filtered_odom_pub_.publish(odom_msg);
}