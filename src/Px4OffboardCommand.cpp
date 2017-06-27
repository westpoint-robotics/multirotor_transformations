/*
 * Px4OffboardCommand.cpp
 *
 *  Created on: Jun 27, 2017
 *      Author: thaus
 */


#include "Px4OffboardCommand.h"

Px4OffboardCommand::Px4OffboardCommand():
  rc_channel_throttle_(rc_channels::RC_CHANNEL_THROTTLE),
  rc_channel_roll_(rc_channels::RC_CHANNEL_ROLL),
  rc_channel_pitch_(rc_channels::RC_CHANNEL_PITCH),
  rc_channel_yaw_(rc_channels::RC_CHANNEL_YAW),
  rc_channel_rc_on_(rc_channels::RC_CHANNEL_RC_ON),
  rc_channel_mode_(rc_channels::RC_CHANNEL_MODE),
  joy_axis_throttle_(joy_axes::JOY_AXIS_THROTTLE),
  joy_axis_roll_(joy_axes::JOY_AXIS_ROLL),
  joy_axis_pitch_(joy_axes::JOY_AXIS_PITCH),
  joy_axis_yaw_(joy_axes::JOY_AXIS_YAW),
  joy_axis_mode_(joy_axes::JOY_AXIS_MODE),
  joy_button_rc_on_(joy_buttons::JOY_BUTTON_RC_ON),
  px4_offboard_state_(offboard_state::OFFBOARD_STATE_OFF),
  px4_mc_yaw_p_(2.8)
{
    // TODO Auto-generated constructor stub
}

Px4OffboardCommand::~Px4OffboardCommand() {
	// TODO Auto-generated destructor stub
}

void Px4OffboardCommand::setJoyPublisher(ros::Publisher joy_pub) {
  joy_pub_ = joy_pub;
}

void Px4OffboardCommand::setParamSetClient(ros::ServiceClient param_set_client) {
  param_set_client_ = param_set_client;
}


void Px4OffboardCommand::rcCallback(const mavros_msgs::RCIn &msg) {

  // first check is rc msg contains any channel value
  if (msg.channels.size() > 0) {

    sensor_msgs::Joy joy_msg;
    std::vector<float> axis_array(12, 0); // length 12, init to 0
    std::vector<int> button_array(12, 0); // length 12, init to 0
    
    joy_msg.axes = axis_array;
    joy_msg.buttons = button_array;

    joy_msg.header = msg.header;
    joy_msg.axes[joy_axis_throttle_] = rcChannelToJoyAxis(msg.channels[rc_channel_throttle_]);
    joy_msg.axes[joy_axis_roll_] = rcChannelToJoyAxis(msg.channels[rc_channel_roll_]);
    joy_msg.axes[joy_axis_pitch_] = rcChannelToJoyAxis(msg.channels[rc_channel_pitch_]);
    joy_msg.axes[joy_axis_yaw_] = rcChannelToJoyAxis(msg.channels[rc_channel_yaw_]);
    joy_msg.axes[joy_axis_mode_] = rcChannelToJoyAxis(msg.channels[rc_channel_mode_]);
    joy_msg.buttons[joy_button_rc_on_] = rcChannelToJoyButton(msg.channels[rc_channel_rc_on_]);

    joy_msg.header.stamp = ros::Time::now();
    joy_pub_.publish(joy_msg);
  }

}

void Px4OffboardCommand::stateCallback(const mavros_msgs::State &msg) {

  std::string px4_mode(msg.mode);
  std::string offboard_mode("OFFBOARD");

  if (px4_mode.compare(offboard_mode) == 0) {
    //ROS_INFO("Offboard mode on");
    if (px4_offboard_state_ == offboard_state::OFFBOARD_STATE_OFF) {
      //transition from off to on 
      // call service to set yaw P gain to 0

      mavros_msgs::ParamSet param_set_service;
      param_set_service.request.param_id = std::string("MC_YAW_P");
      param_set_service.request.value.integer = 0;
      param_set_service.request.value.real = 0.0;

      if (param_set_client_.call(param_set_service)) {

        if (fabs(param_set_service.response.value.real) < 0.0001) {
            ROS_INFO("Turned off yaw controller");
        }
        else {
            ROS_ERROR("Service called but yaw controller not turned off.");
        }


      }
      else {
        ROS_ERROR("Service for turning off yaw control failed.");
      }

      px4_offboard_state_ = offboard_state::OFFBOARD_STATE_ON;
    }
  }
  else {

    if (px4_offboard_state_ == offboard_state::OFFBOARD_STATE_ON) {
      //transition from on to off 
      // call service to set yaw P gain to default value

      mavros_msgs::ParamSet param_set_service;
      param_set_service.request.param_id = std::string("MC_YAW_P");
      param_set_service.request.value.integer = 0;
      param_set_service.request.value.real = px4_mc_yaw_p_;

      if (param_set_client_.call(param_set_service)) {

        if (fabs(param_set_service.response.value.real - px4_mc_yaw_p_) < 0.0001) {
            ROS_INFO("Turned on yaw controller");
        }
        else {
            ROS_ERROR("Service called but yaw controller not turned on.");
        }


      }
      else {
        ROS_ERROR("Service for turning on yaw control failed.");
      }


      px4_offboard_state_ = offboard_state::OFFBOARD_STATE_OFF;
    }

  }

}


float Px4OffboardCommand::rcChannelToJoyAxis(float rc_channel_value) {

  float joy_value;
  joy_value = (rc_channel_value - (rc_channels::RC_CHANNEL_VALUE_MAX + rc_channels::RC_CHANNEL_VALUE_MIN) / 2.0) / ((rc_channels::RC_CHANNEL_VALUE_MAX - rc_channels::RC_CHANNEL_VALUE_MIN) / 2.0); 
  if (joy_value < joy_axes::JOY_AXIS_VALUE_MIN)
    joy_value = joy_axes::JOY_AXIS_VALUE_MIN;
  else if (joy_value > joy_axes::JOY_AXIS_VALUE_MAX)
    joy_value = joy_axes::JOY_AXIS_VALUE_MAX;
  
  return joy_value;
}


uint8_t Px4OffboardCommand::rcChannelToJoyButton(float rc_channel_value) {

  uint8_t joy_value;

  if (rc_channel_value > (rc_channels::RC_CHANNEL_VALUE_MAX + rc_channels::RC_CHANNEL_VALUE_MIN) / 2.0 )
    joy_value = joy_buttons::JOY_BUTTON_VALUE_ON;
  else
    joy_value = joy_buttons::JOY_BUTTON_VALUE_OFF;

  return joy_value;
}