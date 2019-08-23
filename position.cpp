
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

#include "position.h"
geometry_msgs::Pose  position::value_down_pose1(){
    geometry_msgs::Pose     down_pose1;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose1.position.x = -0.532144;
    down_pose1.position.y = -0.490599;
    down_pose1.position.z = 0.029827;
    down_pose1.orientation.x = q.x();
    down_pose1.orientation.y = q.y();
    down_pose1.orientation.z = q.z();
    down_pose1.orientation.w = q.w();
    return down_pose1;
}


geometry_msgs::Pose  position::value_down_pose2(){
    geometry_msgs::Pose     down_pose2;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose2.position.x = -0.527351;
    down_pose2.position.y = -0.488964;
    down_pose2.position.z = 0.044798;
    down_pose2.orientation.x = q.x();
    down_pose2.orientation.y = q.y();
    down_pose2.orientation.z = q.z();
    down_pose2.orientation.w = q.w();
    return down_pose2;
}


geometry_msgs::Pose  position::value_down_pose3(){
    geometry_msgs::Pose     down_pose3;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose3.position.x = -0.522663;
    down_pose3.position.y = -0.487360;
    down_pose3.position.z = 0.058960;
    down_pose3.orientation.x = q.x();
    down_pose3.orientation.y = q.y();
    down_pose3.orientation.z = q.z();
    down_pose3.orientation.w = q.w();
    return down_pose3;
}



geometry_msgs::Pose  position::value_down_pose4(){
    geometry_msgs::Pose     down_pose4;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose4.position.x = -0.518068;
    down_pose4.position.y = -0.483887;
    down_pose4.position.z = 0.074883;
    down_pose4.orientation.x = q.x();
    down_pose4.orientation.y = q.y();
    down_pose4.orientation.z = q.z();
    down_pose4.orientation.w = q.w();
    return down_pose4;
}


geometry_msgs::Pose  position::value_down_pose5(){
    geometry_msgs::Pose     down_pose5;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose5.position.x = -0.513705;
    down_pose5.position.y = -0.482438;
    down_pose5.position.z = 0.092137;
    down_pose5.orientation.x = q.x();
    down_pose5.orientation.y = q.y();
    down_pose5.orientation.z = q.z();
    down_pose5.orientation.w = q.w();
    return down_pose5;
}


geometry_msgs::Pose  position::value_down_pose6(){
    geometry_msgs::Pose     down_pose6;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose6.position.x = -0.509383;
    down_pose6.position.y = -0.481924;
    down_pose6.position.z = 0.108368;
    down_pose6.orientation.x = q.x();
    down_pose6.orientation.y = q.y();
    down_pose6.orientation.z = q.z();
    down_pose6.orientation.w = q.w();
    return down_pose6;
}

geometry_msgs::Pose  position::value_down_pose7(){
    geometry_msgs::Pose     down_pose7;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    down_pose7.position.x = -0.505649;
    down_pose7.position.y = -0.480698;
    down_pose7.position.z = 0.124326;
    down_pose7.orientation.x = q.x();
    down_pose7.orientation.y = q.y();
    down_pose7.orientation.z = q.z();
    down_pose7.orientation.w = q.w();
    return down_pose7;
}

geometry_msgs::Pose  position::value_pose1(){
    geometry_msgs::Pose     pose1;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121); //radian
    pose1.position.x = -0.500311;
    pose1.position.y = -0.478867;
    pose1.position.z = 0.139886;
    pose1.orientation.x = q.x();
    pose1.orientation.y = q.y();
    pose1.orientation.z = q.z();
    pose1.orientation.w = q.w();
    return pose1;
}

geometry_msgs::Pose  position::value_pose2(){
    geometry_msgs::Pose     pose2;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    pose2.position.x = -0.497952;
    pose2.position.y = -0.472601;
    pose2.position.z = 0.158589;
    pose2.orientation.x = q.x();
    pose2.orientation.y = q.y();
    pose2.orientation.z = q.z();
    pose2.orientation.w = q.w();
    return pose2;
}

geometry_msgs::Pose  position::value_pose3(){
    geometry_msgs::Pose     pose3;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    pose3.position.x = -0.493146;
    pose3.position.y = -0.472035;
    pose3.position.z = 0.173761;
    pose3.orientation.x = q.x();
    pose3.orientation.y = q.y();
    pose3.orientation.z = q.z();
    pose3.orientation.w = q.w();
    return pose3;
}

geometry_msgs::Pose  position::value_pose4(){
    geometry_msgs::Pose     pose4;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    pose4.position.x = -0.488381;
    pose4.position.y = -0.470952;
    pose4.position.z = 0.189590;
    pose4.orientation.x = q.x();
    pose4.orientation.y = q.y();
    pose4.orientation.z = q.z();
    pose4.orientation.w = q.w();
    return pose4;
}

geometry_msgs::Pose  position::value_pose5(){
    geometry_msgs::Pose     pose5;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    pose5.position.x = -0.484172;
    pose5.position.y = -0.467424;
    pose5.position.z = 0.205172;
    pose5.orientation.x = q.x();
    pose5.orientation.y = q.y();
    pose5.orientation.z = q.z();
    pose5.orientation.w = q.w();
    return pose5;
}

geometry_msgs::Pose  position::value_pose6(){
    geometry_msgs::Pose     pose6;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    pose6.position.x = -0.479683;
    pose6.position.y = -0.465929;
    pose6.position.z = 0.222612;
    pose6.orientation.x = q.x();
    pose6.orientation.y = q.y();
    pose6.orientation.z = q.z();
    pose6.orientation.w = q.w();
    return pose6;
}

geometry_msgs::Pose  position::value_pose7(){
    geometry_msgs::Pose     pose7;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    pose7.position.x = -0.474914;
    pose7.position.y = -0.467272;
    pose7.position.z = 0.237349;
    pose7.orientation.x = q.x();
    pose7.orientation.y = q.y();
    pose7.orientation.z = q.z();
    pose7.orientation.w = q.w();
    return pose7;
}

geometry_msgs::Pose  position::value_up_pose1(){
    geometry_msgs::Pose     up_pose1;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose1.position.x = -0.469422;
    up_pose1.position.y = -0.466833;
    up_pose1.position.z = 0.254406;
    up_pose1.orientation.x = q.x();
    up_pose1.orientation.y = q.y();
    up_pose1.orientation.z = q.z();
    up_pose1.orientation.w = q.w();
    return up_pose1;
}

geometry_msgs::Pose  position::value_up_pose2(){
    geometry_msgs::Pose     up_pose2;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose2.position.x = -0.466899;
    up_pose2.position.y = -0.462929;
    up_pose2.position.z = 0.269333;
    up_pose2.orientation.x = q.x();
    up_pose2.orientation.y = q.y();
    up_pose2.orientation.z = q.z();
    up_pose2.orientation.w = q.w();
    return up_pose2;
}

geometry_msgs::Pose  position::value_up_pose3(){
    geometry_msgs::Pose     up_pose3;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose3.position.x = -0.462533;
    up_pose3.position.y = -0.461473;
    up_pose3.position.z = 0.285990;
    up_pose3.orientation.x = q.x();
    up_pose3.orientation.y = q.y();
    up_pose3.orientation.z = q.z();
    up_pose3.orientation.w = q.w();
    return up_pose3;
}


geometry_msgs::Pose  position::value_up_pose4(){
    geometry_msgs::Pose     up_pose4;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose4.position.x = -0.459459;
    up_pose4.position.y = -0.460486;
    up_pose4.position.z = 0.301498;
    up_pose4.orientation.x = q.x();
    up_pose4.orientation.y = q.y();
    up_pose4.orientation.z = q.z();
    up_pose4.orientation.w = q.w();
    return up_pose4;
}


geometry_msgs::Pose  position::value_up_pose5(){
    geometry_msgs::Pose     up_pose5;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose5.position.x = -0.454855;
    up_pose5.position.y = -0.458932;
    up_pose5.position.z = 0.317358;
    up_pose5.orientation.x = q.x();
    up_pose5.orientation.y = q.y();
    up_pose5.orientation.z = q.z();
    up_pose5.orientation.w = q.w();
    return up_pose5;
}


geometry_msgs::Pose  position::value_up_pose6(){
    geometry_msgs::Pose     up_pose6;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose6.position.x = -0.449875;
    up_pose6.position.y = -0.464569;
    up_pose6.position.z = 0.330187;
    up_pose6.orientation.x = q.x();
    up_pose6.orientation.y = q.y();
    up_pose6.orientation.z = q.z();
    up_pose6.orientation.w = q.w();
    return up_pose6;
}


geometry_msgs::Pose  position::value_up_pose7(){
    geometry_msgs::Pose     up_pose7;
    tf::Quaternion q;
    q.setRPY(1.586714,-0.90511,0.345121);
    up_pose7.position.x = -0.446624;
    up_pose7.position.y = -0.463532;
    up_pose7.position.z = 0.347147;
    up_pose7.orientation.x = q.x();
    up_pose7.orientation.y = q.y();
    up_pose7.orientation.z = q.z();
    up_pose7.orientation.w = q.w();
    return up_pose7;
}










//std::vector<double> home_position;
//home_position.push_back(23.165562);
//home_position.push_back(57.212379);
//home_position.push_back(-81.686617);
//home_position.push_back(-111.254574);
//home_position.push_back(61.244093);
//home_position.push_back(49.096489);

//tf::Quaternion q;  //用来设置位姿，角度为弧度，三个数据


//geometry_msgs::Pose     down_pose3;
//q.setRPY(1.783028,-1.331835,0.102477); //radian
//down_pose3.position.x = -0.531320;
//down_pose3.position.y = -0.452748;
//down_pose3.position.z = 0.043514;
//down_pose3.orientation.x = q.x();
//down_pose3.orientation.y = q.y();
//down_pose3.orientation.z = q.z();
//down_pose3.orientation.w = q.w();

//geometry_msgs::Pose     down_pose4;
//q.setRPY(1.783028,-1.331835,0.102477); //radian
//down_pose4.position.x = -0.526218;
//down_pose4.position.y = -0.453923;
//down_pose4.position.z = 0.059604;
//down_pose4.orientation.x = q.x();
//down_pose4.orientation.y = q.y();
//down_pose4.orientation.z = q.z();
//down_pose4.orientation.w = q.w();

//geometry_msgs::Pose     down_pose5;
//q.setRPY(1.783028,-1.331835,0.102477); //radian
//down_pose5.position.x = -0.522299;
//down_pose5.position.y = -0.453520;
//down_pose5.position.z = 0.075779;
//down_pose5.orientation.x = q.x();
//down_pose5.orientation.y = q.y();
//down_pose5.orientation.z = q.z();
//down_pose5.orientation.w = q.w();

//geometry_msgs::Pose     down_pose6;
//q.setRPY(1.783028,-1.331835,0.102477); //radian
//down_pose6.position.x = -0.518492;
//down_pose6.position.y = -0.453128;
//down_pose6.position.z = 0.091485;
//down_pose6.orientation.x = q.x();
//down_pose6.orientation.y = q.y();
//down_pose6.orientation.z = q.z();
//down_pose6.orientation.w = q.w();

//geometry_msgs::Pose     down_pose7;
//q.setRPY(1.783028,-1.331835,0.102477); //radian
//down_pose7.position.x = -0.513424;
//down_pose7.position.y = -0.452377;
//down_pose7.position.z = 0.108006;
//down_pose7.orientation.x = q.x();
//down_pose7.orientation.y = q.y();
//down_pose7.orientation.z = q.z();
//down_pose7.orientation.w = q.w();

//geometry_msgs::Pose     pose1;
//q.setRPY(1.783028,-1.331835,0.102477); //radian
//pose1.position.x = -0.509960;
//pose1.position.y = -0.452022;
//pose1.position.z = 0.122301;
//pose1.orientation.x = q.x();
//pose1.orientation.y = q.y();
//pose1.orientation.z = q.z();
//pose1.orientation.w = q.w();

//geometry_msgs::Pose     pose2;
//q.setRPY(1.783028,-1.331835,0.102477);
//pose2.position.x = -0.505763;
//pose2.position.y = -0.451590;
//pose2.position.z = 0.139613;
//pose2.orientation.x = q.x();
//pose2.orientation.y = q.y();
//pose2.orientation.z = q.z();
//pose2.orientation.w = q.w();

//geometry_msgs::Pose     pose3;
//q.setRPY(1.783028,-1.331835,0.102477);
//pose3.position.x = -0.502230;
//pose3.position.y = -0.451226;
//pose3.position.z = 0.154197;
//pose3.orientation.x = q.x();
//pose3.orientation.y = q.y();
//pose3.orientation.z = q.z();
//pose3.orientation.w = q.w();

//geometry_msgs::Pose     pose4;
//q.setRPY(1.783028,-1.331835,0.102477);
//pose4.position.x = -0.498137;
//pose4.position.y = -0.450805;
//pose4.position.z = 0.171087;
//pose4.orientation.x = q.x();
//pose4.orientation.y = q.y();
//pose4.orientation.z = q.z();
//pose4.orientation.w = q.w();

//geometry_msgs::Pose     pose5;
//q.setRPY(1.783028,-1.331835,0.102477);
//pose5.position.x = -0.492472;
//pose5.position.y = -0.454216;
//pose5.position.z = 0.186872;
//pose5.orientation.x = q.x();
//pose5.orientation.y = q.y();
//pose5.orientation.z = q.z();
//pose5.orientation.w = q.w();

//geometry_msgs::Pose     pose6;
//q.setRPY(1.783028,-1.331835,0.102477);
//pose6.position.x = -0.488511;
//pose6.position.y = -0.453807;
//pose6.position.z = 0.203220;
//pose6.orientation.x = q.x();
//pose6.orientation.y = q.y();
//pose6.orientation.z = q.z();
//pose6.orientation.w = q.w();

//geometry_msgs::Pose     pose7;
//q.setRPY(1.783028,-1.331835,0.102477);
//pose7.position.x = -0.483587;
//pose7.position.y = -0.453099;
//pose7.position.z = 0.219674;
//pose7.orientation.x = q.x();
//pose7.orientation.y = q.y();
//pose7.orientation.z = q.z();
//pose7.orientation.w = q.w();

//geometry_msgs::Pose     up_pose1;
//q.setRPY(1.783028,-1.331835,0.102477);
//up_pose1.position.x = -0.479871;
//up_pose1.position.y = -0.452717;
//up_pose1.position.z = 0.235006;
//up_pose1.orientation.x = q.x();
//up_pose1.orientation.y = q.y();
//up_pose1.orientation.z = q.z();
//up_pose1.orientation.w = q.w();

//geometry_msgs::Pose     up_pose2;
//q.setRPY(1.783028,-1.331835,0.102477);
//up_pose2.position.x = -0.473710;
//up_pose2.position.y = -0.451689;
//up_pose2.position.z = 0.252890;
//up_pose2.orientation.x = q.x();
//up_pose2.orientation.y = q.y();
//up_pose2.orientation.z = q.z();
//up_pose2.orientation.w = q.w();

//geometry_msgs::Pose     up_pose3;
//q.setRPY(1.783028,-1.331835,0.102477);
//up_pose3.position.x = -0.469983;
//up_pose3.position.y = -0.451306;
//up_pose3.position.z = 0.268272;
//up_pose3.orientation.x = q.x();
//up_pose3.orientation.y = q.y();
//up_pose3.orientation.z = q.z();
//up_pose3.orientation.w = q.w();

//geometry_msgs::Pose     up_pose4;
//q.setRPY(1.783028,-1.331835,0.102477);
//up_pose4.position.x = -0.465356;
//up_pose4.position.y = -0.453179;
//up_pose4.position.z = 0.284254;
//up_pose4.orientation.x = q.x();
//up_pose4.orientation.y = q.y();
//up_pose4.orientation.z = q.z();
//up_pose4.orientation.w = q.w();

//geometry_msgs::Pose     up_pose5;
//q.setRPY(1.783028,-1.331835,0.102477);
//up_pose5.position.x = -0.461512;
//up_pose5.position.y = -0.452784;
//up_pose5.position.z = 0.300116;
//up_pose5.orientation.x = q.x();
//up_pose5.orientation.y = q.y();
//up_pose5.orientation.z = q.z();
//up_pose5.orientation.w = q.w();


