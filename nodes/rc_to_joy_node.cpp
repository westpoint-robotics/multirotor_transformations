#include "RcToJoy.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "rc_to_joy");
  ros::NodeHandle n;

  RcToJoy *rc_to_joy_node = new RcToJoy();

  ros::Subscriber rc_sub = n.subscribe("mavros/rc/in", 1, &RcToJoy::rcCallback, rc_to_joy_node);

  ros::Publisher joy_pub = n.advertise<sensor_msgs::Joy>("px4/joy", 1);

  rc_to_joy_node->setJoyPublisher(joy_pub);

  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spin();
  }

  delete rc_to_joy_node;
  return 0;
} // end main()
