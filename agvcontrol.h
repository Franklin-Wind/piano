#ifndef AGVCONTROL_H
#define AGVCONTROL_H

#include "ros/ros.h"
#include <ros/callback_queue.h>
#include <math.h>
#include <tf/transform_broadcaster.h>
#include "geometry_msgs/Pose2D.h"
#include "serial/serial.h"
#include "std_msgs/String.h"
#include <sstream>

#include <string>

#include <signal.h>
#include <termios.h>
#include <stdio.h>

#include <pthread.h>
#include <unistd.h>
#include <geometry_msgs/Twist.h>
#include <thread>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <time.h>

#include "boost/thread/mutex.hpp"
#include "boost/thread/thread.hpp"
#include "ros/console.h"
#include "aubo_msgs/SerialFrame.h"
#include <iostream>
#include <unistd.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>
#define LX 0.58f
#define LIN_VEL_MAX 0.5f
#define ANG_VEL_MAX (LIN_VEL_MAX/LX)

#define FRAME_HEAD1  				0xEB
#define FRAME_HEAD2  				0x90
#define FRAME_HEAD1_RT  			0xEE
#define FRAME_HEAD2_RT  			0x16
#define  Hands_ID  1


#define CMD_MC_SET_DRVALL_SEEKPOS 						0x50
#define CMD_MC_SET_DRVALL_SPEED 						0x51
#define CMD_MC_SET_DRVALL_YBP_THRESHOLD						0x52
#define CMD_MC_SET_DRVALL_SEEKANGLE						0x53
#define CMD_MC_SET_DRVALL_SEEKANGLE_GYH						0x54
#define CMD_MC_SET_DJ_TURN							0x55
    
    
#define CMD_MC_READ_DRVALL_SEEKPOS 						0xD0
#define CMD_MC_READ_DRVALL_CURPOS 						0xD1
#define CMD_MC_READ_DRVALL_SPEED 						0xD2
#define CMD_MC_READ_DRVALL_YBP_THRESHOLD					0xD3
#define CMD_MC_READ_DRVALL_YBP_RAWDATA						0xD4
#define CMD_MC_READ_DRVALL_SEEKANGLE 						0xD5
#define CMD_MC_READ_DRVALL_CURANGLE 						0xD6
#define CMD_MC_READ_DRVALL_SEEKGYHANGLE 					0xD7
#define CMD_MC_READ_DJ_TURN							0xD8
#define CMD_MC_READ_DRVALL_CURANGLE_GYH						0xD9
#define CMD_MC_READ_BIT								0xDA
    
    
#define CMD_MC_PARA_SAVE 							0x01
#define CMD_MC_PARA_READ 							0x02
#define CMD_MC_PARA_USED_DEF							0x03
#define CMD_MC_PARA_ID_SET							0x04
#define CMD_MC_MOVE_K_SET_CURPOS_IN_CMAP					0x05
#define CMD_MC_MOVE_K_SHOW							0x06
#define CMD_MC_MOVE_K_SHOW_ASDEFAULT						0x07
uint16_t Set_Hand_data1,Set_Hand_data2,Set_Hand_data3,Set_Hand_data4,Set_Hand_data5,Set_Hand_data6=0 ;
uint16_t current_angle1,current_angle2,current_angle3,current_angle4,current_angle5,current_angle6=0;
namespace agvcontrol {


//-----------------------------------------
class AGVControl
{
public:
    AGVControl();
    ~AGVControl();

    int Com_Hands_AngleSet1(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6);
    int Com_Hands_AngleSet2();
    int Com_Hands_AngleSet3(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6);

    void play(int k,int ms);

private:

    ros::NodeHandle nh_;
    ros::Publisher write_pub_;
    ros::Publisher state_pub_;
    ros::Subscriber receive_sub_;
    ros::CallbackQueue my_queue;
    std::thread* rt_publish_thread_;


};


} //end of namespace
#endif // AGVCONTROL_H
