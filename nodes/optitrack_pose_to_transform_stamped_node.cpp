#include "OptitrackPoseToTransformStamped.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "pose_stamped_to_transform_stamped");
  ros::NodeHandle n;
  ros::NodeHandle n_private("~");

  OptitrackPoseToTransformStamped *transform_node = new OptitrackPoseToTransformStamped();

  // remap this topic runtime
  ros::Subscriber pose_stamped_sub = n.subscribe("optitrack_pose", 1, &OptitrackPoseToTransformStamped::optitrackPoseCallback, transform_node, ros::TransportHints().tcpNoDelay());

  // remap this topic on runtime
  ros::Publisher transform_stamped_pub = n.advertise<geometry_msgs::TransformStamped>("transform_stamped", 1);
  ros::Publisher pose_stamped_pub = n.advertise<geometry_msgs::PoseStamped>("pose_nwu", 1);

  std::string marker_name;
  if (n_private.getParam("marker_name", marker_name))
  {
      ROS_INFO("Got param: %s", marker_name.c_str());
  }
  else
  { 
      marker_name = std::string("marker");
      ROS_ERROR("Failed to get param 'marker_name', using default value 'marker'.");
  }


  transform_node->setTransformStampedPublisher(transform_stamped_pub);
  transform_node->setPoseStampedPublisher(pose_stamped_pub);
  transform_node->setMarkerName(marker_name);

  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spin();
  }

  delete transform_node;
  return 0;
} // end main()
