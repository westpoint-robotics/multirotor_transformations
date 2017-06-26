#include "MpcToPx4Command.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "mpc_to_px4_command");
  ros::NodeHandle n;

  MpcToPx4Command *transform_node = new MpcToPx4Command();

  ros::Subscriber mpc_cmd_sub = n.subscribe("command/roll_pitch_yawrate_thrust", 1, &MpcToPx4Command::mpcCmdCallback, transform_node);

  ros::Publisher px4_attitude_cmd_pub = n.advertise<geometry_msgs::PoseStamped>("setpoint_attitude/attitude", 1);
  ros::Publisher px4_thrust_cmd_pub = n.advertise<std_msgs::Float64>("setpoint_attitude/att_throttle", 1);

  transform_node->setPx4AttitudeCmdPublisher(px4_attitude_cmd_pub);
  transform_node->setPx4ThrustCmdPublisher(px4_thrust_cmd_pub);

  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spin();
  }

  delete transform_node;
  return 0;
} // end main()
