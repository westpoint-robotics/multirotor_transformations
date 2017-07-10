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

  OptitrackPoseToTransformStamped *transform_node = new OptitrackPoseToTransformStamped();

  // remap this topic runtime
  ros::Subscriber pose_stamped_sub = n.subscribe("optitrack_pose", 1, &OptitrackPoseToTransformStamped::optitrackPoseCallback, transform_node, ros::TransportHints().tcpNoDelay());

  // remap this topic on runtime
  ros::Publisher transform_stamped_pub = n.advertise<geometry_msgs::TransformStamped>("transform_stamped", 1);
  //ros::Publisher pose_stamped_pub = n.advertise<geometry_msgs::PoseStamped>("mavros/mocap/pose", 1);


  transform_node->setTransformStampedPublisher(transform_stamped_pub);
  //transform_node->setPoseStampedPublisher(pose_stamped_pub);


  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spin();
  }

  delete transform_node;
  return 0;
} // end main()
