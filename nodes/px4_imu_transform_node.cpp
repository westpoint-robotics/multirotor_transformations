#include "Px4ImuTransform.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "px4_imu_transform");
  ros::NodeHandle n;

  Px4ImuTransform *transform_node = new Px4ImuTransform();

  // remap this topic runtime
  ros::Subscriber pose_stamped_sub = n.subscribe("mavros/imu/data", 1, &Px4ImuTransform::imuCallback, transform_node, ros::TransportHints().tcpNoDelay());

  // remap this topic on runtime
  ros::Publisher imu_transformed_pub = n.advertise<sensor_msgs::Imu>("px4/imu", 1);

  transform_node->setTransformedImuPublisher(imu_transformed_pub);

  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spin();
  }

  delete transform_node;
  return 0;
} // end main()
