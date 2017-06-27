/*
 * Px4OffboardCommand.h
 *
 *  Created on: Jun 27, 2017
 *      Author: thaus
 */

#ifndef PX4OFFBOARDCOMMAND_H_
#define PX4OFFBOARDCOMMAND_H_

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "mavros_msgs/RCIn.h"
#include "mavros_msgs/State.h"
#include "mavros_msgs/ParamSet.h"
#include <stdio.h>
#include <math.h>

struct rc_channels
{
  static constexpr float RC_CHANNEL_VALUE_MAX = 1900.0f;             //!< Maximum value of the rc channels.
  static constexpr float RC_CHANNEL_VALUE_MIN = 1100.0f;             //!< Minimum value of the rc channels.

  static const uint8_t RC_CHANNEL_THROTTLE = 2;               //!< Rc channel number used for throttle control
  static const uint8_t RC_CHANNEL_ROLL = 0;                   //!< Rc channel number used for roll control
  static const uint8_t RC_CHANNEL_PITCH = 1;                  //!< Rc channel number used for pitch control
  static const uint8_t RC_CHANNEL_YAW = 3;                    //!< Rc channel number used for yaw control
  static const uint8_t RC_CHANNEL_RC_ON = 6;                  //!< Rc channel number used for selection of RC as reference source (in eth mpc controller)
  static const uint8_t RC_CHANNEL_MODE = 7;                   //!< Rc channel number used for mode selection (manual, altitude hold, position hold)
};


struct joy_axes
{

  static constexpr float JOY_AXIS_VALUE_MAX = 1.0f;           //!< Maximum value of joy axis.
  static constexpr float JOY_AXIS_VALUE_MIN = -1.0f;          //!< Minimum value of joy axis.

  static const uint8_t JOY_AXIS_THROTTLE = 2;             //!< Joy axis number used for throttle control
  static const uint8_t JOY_AXIS_ROLL = 1;                 //!< Joy axis number used for roll control
  static const uint8_t JOY_AXIS_PITCH = 0;                //!< Joy axis number used for pitch control
  static const uint8_t JOY_AXIS_YAW = 3;                  //!< Joy axis number used for yaw control
  static const uint8_t JOY_AXIS_MODE = 4;                 //!< Joy axis number used for mode selection (manual, altitude hold, position hold)
  static const uint8_t JOY_AXIS_CONTROL_INTERFACE = 5;    //!< Joy axis number used for turning on and off control interface (not used in current version)
  static const uint8_t JOY_AXIS_WHEEL = 6;    			  //!< Joy axis number used for wheel !? (not used in current version)

};

struct joy_buttons
{

  static const uint8_t JOY_BUTTON_VALUE_ON = 1;          //!< The joy value when button is pressed
  static const uint8_t JOY_BUTTON_VALUE_OFF = 0;         //!< The joy value when button is NOT pressed

  static const uint8_t JOY_BUTTON_RC_ON = 0;              //!< Joy button number used for selection of RC as reference source (in eth mpc controller)
};

struct offboard_state
{

  static const uint8_t OFFBOARD_STATE_ON = 1;              //!< Flag when offboard mode is activated
  static const uint8_t OFFBOARD_STATE_OFF = 0;             //!< Flag when offboard mode is deactivated

};



class Px4OffboardCommand {
public:

  Px4OffboardCommand();
  virtual ~Px4OffboardCommand();
  void rcCallback(const mavros_msgs::RCIn &msg);
  void stateCallback(const mavros_msgs::State &msg);
  
  void setJoyPublisher(ros::Publisher publisher);
  void setParamSetClient(ros::ServiceClient param_set_client);
 
 private:   
  float rcChannelToJoyAxis(float rc_channel_value);
 	uint8_t rcChannelToJoyButton(float rc_channel_value);
   
  ros::Publisher joy_pub_;
  ros::ServiceClient param_set_client_;

  uint8_t rc_channel_throttle_;
  uint8_t rc_channel_roll_;
  uint8_t rc_channel_pitch_;
  uint8_t rc_channel_yaw_;
  uint8_t rc_channel_rc_on_;
  uint8_t rc_channel_mode_;

  uint8_t joy_axis_throttle_;
  uint8_t joy_axis_roll_;
  uint8_t joy_axis_pitch_;
  uint8_t joy_axis_yaw_;
  uint8_t joy_axis_mode_;
  uint8_t joy_button_rc_on_;

  uint8_t px4_offboard_state_;  // on or off

  float px4_mc_yaw_p_;

};

#endif /* PX4OFFBOARDCOMMAND_H_ */
