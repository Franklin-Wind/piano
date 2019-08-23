#ifndef POSITION_H
#define POSITION_H


#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <tf/LinearMath/Quaternion.h>

#include <std_msgs/String.h>

#include <iostream>

class position{
public:
    geometry_msgs::Pose value_down_pose1();
    geometry_msgs::Pose value_down_pose2();
    geometry_msgs::Pose value_down_pose3();
    geometry_msgs::Pose value_down_pose4();
    geometry_msgs::Pose value_down_pose5();
    geometry_msgs::Pose value_down_pose6();
    geometry_msgs::Pose value_down_pose7();
    geometry_msgs::Pose value_pose1();
    geometry_msgs::Pose value_pose2();
    geometry_msgs::Pose value_pose3();
    geometry_msgs::Pose value_pose4();
    geometry_msgs::Pose value_pose5();
    geometry_msgs::Pose value_pose6();
    geometry_msgs::Pose value_pose7();
    geometry_msgs::Pose value_up_pose1();
    geometry_msgs::Pose value_up_pose2();
    geometry_msgs::Pose value_up_pose3();
    geometry_msgs::Pose value_up_pose4();
    geometry_msgs::Pose value_up_pose5();
    geometry_msgs::Pose value_up_pose6();
    geometry_msgs::Pose value_up_pose7();


};






#endif // POSITION_H
