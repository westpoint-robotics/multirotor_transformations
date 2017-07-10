#include "MarkerOptitrack.h"


/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "marker_optitrack");
  ros::NodeHandle n;

  MarkerOptitrack *node = new MarkerOptitrack();

  // remap this topic runtime
  ros::Subscriber uav_pose_sub = n.subscribe("vrpn_client_node/uav/pose", 1, &MarkerOptitrack::uavPoseCallback, node, ros::TransportHints().tcpNoDelay());
  ros::Subscriber marker_pose_sub = n.subscribe("vrpn_client_node/marker/pose", 1, &MarkerOptitrack::markerPoseCallback, node, ros::TransportHints().tcpNoDelay());

  // remap this topic on runtime
  ros::Publisher uav_relative_pose_pub = n.advertise<geometry_msgs::PoseStamped>("uav_relative_pose", 1);


  node->setUavRelativePosePublisher(uav_relative_pose_pub);

  tf::Transform uav_to_world;
  tf::Transform marker_to_world;
  tf::Transform uav_to_marker;
  geometry_msgs::PoseStamped uav_relative_pose;
  // Main loop.
  while (n.ok())
  {
    // everything happens within callback so jus spin
      ros::spinOnce();
      if (node->isNewUavPoseReceived() && node->isNewMarkerPoseReceived()) {
        // do something
        uav_to_world.setOrigin(tf::Vector3(node->uav_pose.pose.position.x,
                                           node->uav_pose.pose.position.y,
                                           node->uav_pose.pose.position.z));
        uav_to_world.setRotation(tf::Quaternion(node->uav_pose.pose.orientation.x,
                                                node->uav_pose.pose.orientation.y,
                                                node->uav_pose.pose.orientation.z,
                                                node->uav_pose.pose.orientation.w));
        marker_to_world.setOrigin(tf::Vector3(node->marker_pose.pose.position.x,
                                           node->marker_pose.pose.position.y,
                                           node->marker_pose.pose.position.z));
        marker_to_world.setRotation(tf::Quaternion(node->marker_pose.pose.orientation.x,
                                                node->marker_pose.pose.orientation.y,
                                                node->marker_pose.pose.orientation.z,
                                                node->marker_pose.pose.orientation.w));

        tf::Matrix3x3 mt(uav_to_world.getRotation());
        /*
        ROS_INFO("\n %.2f %.2f %.2f %.2f \n %.2f %.2f %.2f %.2f \n %.2f %.2f %.2f %.2f",
                  mt[0][0], mt[0][1], mt[0][2], uav_to_world.getOrigin().getX(),
                  mt[1][0], mt[1][1], mt[1][2], uav_to_world.getOrigin().getY(),
                  mt[2][0], mt[2][1], mt[2][2], uav_to_world.getOrigin().getZ());
        */
        tf::Transform tf1 = marker_to_world.inverse();
        tf::Matrix3x3 mt1(tf1.getRotation());
      /*
        ROS_INFO("\n %.2f %.2f %.2f %.2f \n %.2f %.2f %.2f %.2f \n %.2f %.2f %.2f %.2f",
                  mt1[0][0], mt1[0][1], mt1[0][2], tf1.getOrigin().getX(),
                  mt1[1][0], mt1[1][1], mt1[1][2], tf1.getOrigin().getY(),
                  mt1[2][0], mt1[2][1], mt1[2][2], tf1.getOrigin().getZ());
*/
        uav_to_marker = marker_to_world.inverse() * uav_to_world;

        uav_relative_pose.pose.position.x = uav_to_marker.getOrigin().getX();
        uav_relative_pose.pose.position.y = uav_to_marker.getOrigin().getY();
        uav_relative_pose.pose.position.z = uav_to_marker.getOrigin().getZ();

        uav_relative_pose.pose.orientation.x = uav_to_marker.getRotation().getX();
        uav_relative_pose.pose.orientation.y = uav_to_marker.getRotation().getY();
        uav_relative_pose.pose.orientation.z = uav_to_marker.getRotation().getZ();
        uav_relative_pose.pose.orientation.w = uav_to_marker.getRotation().getW();

        uav_relative_pose.header.stamp = ros::Time::now();  

        //ROS_INFO("Finished transformation, publishing");

        node->publishUavRelativePose(uav_relative_pose);

        node->clearNewUavPoseFlag();
        node->clearNewMarkerPoseFlag();
      }
  }

  delete node;
  return 0;
} // end main()
