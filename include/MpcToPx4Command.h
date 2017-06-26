/*
 * MpcToPx4Command.h
 *
 *  Created on: Jun 24, 2017
 *      Author: thaus
 */

#ifndef MPCTOPX4COMMAND_H_
#define MPCTOPX4COMMAND_H_

#include "ros/ros.h"
#include "mav_msgs/RollPitchYawrateThrust.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Float64.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <stdio.h>
#include <math.h>

class MpcToPx4Command {
public:

    MpcToPx4Command();
    virtual ~MpcToPx4Command();
    void mpcCmdCallback(const mav_msgs::RollPitchYawrateThrust &msg);
    
    void setPx4AttitudeCmdPublisher(ros::Publisher publisher);
    void setPx4ThrustCmdPublisher(ros::Publisher publisher);
 
 private:   
 
    ros::Publisher px4_attitude_cmd_pub_;
    ros::Publisher px4_thrust_cmd_pub_;
    float thrust_max_;
};

#endif /* MPCTOPX4COMMAND_H_ */
