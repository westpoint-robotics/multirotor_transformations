cmake_minimum_required(VERSION 2.8.3)
project(multirotor_transformations)

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

cs_add_library(Px4ImuTransform src/Px4ImuTransform.cpp)
target_link_libraries(Px4ImuTransform ${catkin_LIBRARIES})

cs_add_executable(px4_imu_transform_node nodes/px4_imu_transform_node.cpp)
target_link_libraries(px4_imu_transform_node Px4ImuTransform ${catkin_LIBRARIES})

cs_add_library(RcToJoy src/RcToJoy.cpp)
target_link_libraries(RcToJoy ${catkin_LIBRARIES})

cs_add_executable(rc_to_joy_node nodes/rc_to_joy_node.cpp)
target_link_libraries(rc_to_joy_node RcToJoy ${catkin_LIBRARIES})

cs_add_library(MpcToPx4Command src/MpcToPx4Command.cpp)
target_link_libraries(MpcToPx4Command ${catkin_LIBRARIES})

cs_add_executable(mpc_to_px4_command_node nodes/mpc_to_px4_command_node.cpp)
target_link_libraries(mpc_to_px4_command_node MpcToPx4Command ${catkin_LIBRARIES})

cs_add_library(Px4OffboardCommand src/Px4OffboardCommand.cpp)
target_link_libraries(Px4OffboardCommand ${catkin_LIBRARIES})

cs_add_executable(px4_offboard_command_node nodes/px4_offboard_command_node.cpp)
target_link_libraries(px4_offboard_command_node Px4OffboardCommand ${catkin_LIBRARIES})

cs_install()
cs_export()
