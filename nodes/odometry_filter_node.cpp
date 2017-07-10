#include "OdometryFilter.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "odometry_filter");
  ros::NodeHandle n;
  ros::NodeHandle private_node_handle_("~");
  float filter_time_constant, filter_sampling_time;

  OdometryFilter *node = new OdometryFilter();

  // remap this topic runtime
  ros::Subscriber odom_sub = n.subscribe("msf_core/odometry", 1, &OdometryFilter::odomCallback, node, ros::TransportHints().tcpNoDelay());

  // remap this topic on runtime
  ros::Publisher filtered_odom_pub = n.advertise<nav_msgs::Odometry>("msf_core/odometry_filtered", 1);

  node->setFilteredOdomPublisher(filtered_odom_pub);

  private_node_handle_.getParam("filter_time_constant", filter_time_constant);
  private_node_handle_.getParam("filter_sampling_time", filter_sampling_time);
  
  node->setFilterTimeConstant(filter_time_constant);
  node->setFilterSamplingTime(filter_sampling_time);
  node->updateFilterCoefficients();

  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so just spin
      ros::spinOnce();
      ros::Duration(0.001).sleep();
  }

  delete node;
  return 0;
} // end main()
