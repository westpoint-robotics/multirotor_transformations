#include "Px4OffboardCommand.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "rc_to_joy");
  ros::NodeHandle n;

  Px4OffboardCommand *px4_offboard_command_node = new Px4OffboardCommand();

  ros::Subscriber rc_sub = n.subscribe("mavros/rc/in", 1, &Px4OffboardCommand::rcCallback, px4_offboard_command_node);
  ros::Subscriber px4_state_sub = n.subscribe("mavros/state", 1, &Px4OffboardCommand::stateCallback, px4_offboard_command_node);
  ros::ServiceClient param_set_client = n.serviceClient<mavros_msgs::ParamSet>("mavros/param/set");

  ros::Publisher joy_pub = n.advertise<sensor_msgs::Joy>("px4/joy", 1);

  px4_offboard_command_node->setJoyPublisher(joy_pub);
  px4_offboard_command_node->setParamSetClient(param_set_client);

  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spin();
  }

  delete px4_offboard_command_node;
  return 0;
} // end main()
