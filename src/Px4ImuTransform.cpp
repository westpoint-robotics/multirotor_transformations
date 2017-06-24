/*
 * Px4ImuTransform.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: thaus
 */


#include "Px4ImuTransform.h"

Px4ImuTransform::Px4ImuTransform() {
    // TODO Auto-generated constructor stub
}

Px4ImuTransform::~Px4ImuTransform() {
	// TODO Auto-generated destructor stub
}

void Px4ImuTransform::setTransformedImuPublisher(ros::Publisher transformed_imu_pub) {
        transformed_imu_pub_ = transformed_imu_pub;
}


void Px4ImuTransform::imuCallback(const sensor_msgs::Imu &msg) {

  sensor_msgs::Imu imu_msg;
  double covariance_dummy;

  // copy all data to new message
  imu_msg = msg;

  // PX4 Mavros ACC frame (NWU)! to PX4 body frame (NED)
  // since we just change the sign of y and y axis, we don't have to change covariance 
  // acceleration
  imu_msg.linear_acceleration.x = msg.linear_acceleration.x;
  imu_msg.linear_acceleration.y = -msg.linear_acceleration.y;
  imu_msg.linear_acceleration.z = -msg.linear_acceleration.z;

  // angular velocity 
  // PX4 Mavros gyro (NWU) to PX4 body frame (NED)
  imu_msg.angular_velocity.x = msg.angular_velocity.x;
  imu_msg.angular_velocity.y = -msg.angular_velocity.y;
  imu_msg.angular_velocity.z = -msg.angular_velocity.z;

  // quaternion
  // PX4 imu quaternion is in SED frame !
  // covariance is the same for all axes so we don't have to change
  imu_msg.orientation.x = -msg.orientation.x;
  imu_msg.orientation.y =  msg.orientation.y;
  imu_msg.orientation.z =  msg.orientation.z;
  imu_msg.orientation.w =  -msg.orientation.w;

  transformed_imu_pub_.publish(imu_msg);

}