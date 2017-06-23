cmake_minimum_required(VERSION 2.8.3)
project(misc_transformations)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

#generate_dynamic_reconfigure_options(
#  cfg/
#)

include_directories(${catkin_INCLUDE_DIRS} include)

cs_add_library(OptitrackPoseToTransformStamped src/OptitrackPoseToTransformStamped.cpp)
target_link_libraries(OptitrackPoseToTransformStamped ${catkin_LIBRARIES})

cs_add_executable(optitrack_pose_to_transform_stamped_node nodes/optitrack_pose_to_transform_stamped_node.cpp)
target_link_libraries(optitrack_pose_to_transform_stamped_node OptitrackPoseToTransformStamped ${catkin_LIBRARIES})

cs_install()
cs_export()
