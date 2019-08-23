/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, SRI International
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of SRI International nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  Author: zhaoyu
 *  email : zhaoyu@aubo-robotics.cn
 *  note  :
 *          The notes are divided into Chinese and English, which is convenient for global robot engineers to learn ROS control AUBO robots.
 *
 *
 *********************************************************************/
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <tf/LinearMath/Quaternion.h>
#include <std_msgs/String.h>
#include "agvcontrol.h"
#include "ros/ros.h"
#include "position.h"
#include <iostream>
#include <fstream>
#include <string>


struct Pitch{
    int num;
    std::string type;
    std::string tie;
    std::string dot;
    int finger;
    int duration;
};
Pitch pitch[10000];



namespace agvcontrol {

AGVControl::AGVControl()
{
    std::cout << "into AGVControl()" << std::endl;

    write_pub_ = nh_.advertise<aubo_msgs::SerialFrame>("serial_write", 1000, true);     //定义一个发布对象，发布到serial_write话题

}
AGVControl::~AGVControl() {
}


//自动回弹手指控制函数
int AGVControl::Com_Hands_AngleSet1(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6)
{

           aubo_msgs::SerialFrame frame;
            int st = 0;
            short int temp_seekpos_array[6] = { 0 };
            int i = 0;
            unsigned int sum = 0;

            frame.header.stamp = ros::Time::now();
            frame.head1=FRAME_HEAD1;
            frame.head2=FRAME_HEAD2;
            frame.id=Hands_ID;
            sum=sum+frame.id;
            frame.len=0x0D;
            sum=sum+frame.len;
            frame.data.resize(frame.len);
            frame.cmd=CMD_MC_SET_DRVALL_SEEKPOS;
            sum=sum+frame.cmd;

            temp_seekpos_array[0] = dat1;

            temp_seekpos_array[1] = dat2;

            temp_seekpos_array[2] = dat3;

            temp_seekpos_array[3] = dat4;

            temp_seekpos_array[4] = dat5;

            temp_seekpos_array[5] = dat6;

            for (i = 0; i < 6; i++)

            {

                frame.data[i * 2] = (temp_seekpos_array[i] & 0xFF);
                sum=sum+frame.data[i * 2];

                frame.data[i * 2 + 1] = ((temp_seekpos_array[i] >> 8) & 0xFF);
                sum=sum+frame.data[i * 2+1];
            }
            frame.data[frame.len-1]=sum &0xff;


            write_pub_.publish(frame);

            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //50ms后回弹手指
            Com_Hands_AngleSet2();

            return 1;
}
int AGVControl::Com_Hands_AngleSet2()   //回弹手指函数
{
  aubo_msgs::SerialFrame frame;
   int st = 0;
   short int temp_seekpos_array[6] = { 0 };
   int i = 0;
   unsigned int sum = 0;

   frame.header.stamp = ros::Time::now();
   frame.head1=FRAME_HEAD1;
   frame.head2=FRAME_HEAD2;
   frame.id=Hands_ID;
   sum=sum+frame.id;
   frame.len=0x0D;
   sum=sum+frame.len;
   frame.data.resize(frame.len);
   frame.cmd=CMD_MC_SET_DRVALL_SEEKPOS;
   sum=sum+frame.cmd;
   temp_seekpos_array[0] = 1600; //手指初始位置数值   保持与琴键接近且平行

   temp_seekpos_array[1] = 1400;

   temp_seekpos_array[2] = 1500;

   temp_seekpos_array[3] = 1580;

   temp_seekpos_array[4] = 0;

   temp_seekpos_array[5] = 0;

   for (i = 0; i < 6; i++)

   {

       frame.data[i * 2] = (temp_seekpos_array[i] & 0xFF);
       sum=sum+frame.data[i * 2];

       frame.data[i * 2 + 1] = ((temp_seekpos_array[i] >> 8) & 0xFF);
       sum=sum+frame.data[i * 2+1];
   }
   frame.data[frame.len-1]=sum &0xff;


   write_pub_.publish(frame);

   return 1;
}
void AGVControl::play(int k, int ms=250){          //默认停顿时间为250ms

    switch (k){
    case 4:
        Com_Hands_AngleSet1(1400,1400,1500,1580,0,0);
        break;
    case 3:
        Com_Hands_AngleSet1(1600,1000,1500,1580,0,0);
        break;
    case 2:
        Com_Hands_AngleSet1(1600,1400,1240,1580,0,0);
        break;
    case 1:
        Com_Hands_AngleSet1(1600,1400,1500,1300,0,0);
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));


}

}// end of namespace


void Arm_control(geometry_msgs::Pose  pose, int finger, int duration,moveit::planning_interface::MoveGroupInterface *pt,agvcontrol::AGVControl *pr){


  // Reduce the speed of the robot arm by the scaling factor of the maximum speed of each joint. Please note that this is not the speed of the final effector.
  //move_group.setMaxVelocityScalingFactor(1);
  // We want the Cartesian path to be interpolated at a resolution of 1 cm.
  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;           //(The jump threshold is set to 0.0)
  const double eef_step = 0.01;                //(interpolation step)


  double fraction ;
  int    attempts ;

  // Call the planner for planning calculations Note: This is just planning
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  std::vector<geometry_msgs::Pose> waypoints;


    waypoints.push_back(pose);
    fraction = 0.0;
    attempts = 0;
    while(fraction < 1 and attempts < 100){
       fraction = pt->computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
       attempts++;
    }
    waypoints.clear();
    if(fraction == 1.0)
    {

       my_plan.trajectory_= trajectory;
       pt->execute(my_plan);
       pr->play(finger,duration);
    }
    else
    {
       ROS_INFO("exit");
    }
    ROS_INFO_NAMED("tutorial", "Visualizing plan3  (Cartesian path) (%.2f%% acheived)  attemps:%d", fraction * 100.0,attempts);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle nh;

  // Start a thread;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  position dot;  //创建一个对象，为具体某坐标点

  int tag=0;

  agvcontrol::AGVControl control; //创建一个对象，控制手指
  agvcontrol::AGVControl *pr;
  pr = &control;

  // Define the planning group name
  static const std::string PLANNING_GROUP = "manipulator_i5";

  // Create a planning group interface object and set up a planning group
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  moveit::planning_interface::MoveGroupInterface *pt;
  pt = &move_group;
  //********************************************************************************readfile

  std::ifstream myfile("/home/franklin/Desktop/xml2vec-master/planning_result.txt");

  char c;
  int line=0;
  while (myfile.get(c)) {
      if (c == '\n')
          line++;
  }
  //std::cout<<line<<std::endl;

  std::ifstream myfile2("/home/franklin/Desktop/xml2vec-master/planning_result.txt");
  int m=3;     //
  std::string **swp;      //动态申请二维数组 line行 m列
  swp=new std::string*[line];
  for(int i=0;i<line;i++)
  swp[i]=new std::string[m];

  for(int i=0;i<line;i++){
      for(int j=0;j<m;j++){
          myfile2 >> swp[i][j];
      }
  }


  for (int i=0; i<line; i++){
      pitch[i].num  = stoi(swp[i][0]);
      pitch[i].finger = stoi(swp[i][1]);
      pitch[i].duration  = stoi(swp[i][2]);

      //std::cout << pitch[i].num <<"\t"<< pitch[i].finger<<"\t"<<pitch[i].duration<<"\n";
  }

  myfile2.close();
  //**************************************************************************************


  //**************************控制灵巧手和机械臂开始实际运动***********************************
  for (int i=0; i<line; i++) {
      switch (pitch[i].num) {
      case 410:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_down_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_down_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 420:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_down_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 430:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 440:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 450:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 460:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 470:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 510:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 520:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_up_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 530:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_up_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_up_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 540:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_up_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_up_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_up_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 550:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_up_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_up_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_up_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }


      case 560:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_up_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_up_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_up_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 570:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_up_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_up_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_up_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_up_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }




      case 370:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_down_pose7(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_down_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_down_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 360:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_down_pose6(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_down_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_down_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 350:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_down_pose5(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_down_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_down_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 340:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_down_pose4(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_down_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 3:
              Arm_control(dot.value_down_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 4:
              Arm_control(dot.value_down_pose1(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          default: std::cout<<"the value of finger is a wrong number"<<std::endl;break;
          }
          break;
      }

      case 330:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_down_pose3(),pitch[i].finger,pitch[i].duration,pt,pr);break;
          case 2:
              Arm_control(dot.value_down_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;

          default: Arm_control(dot.value_down_pose1(),3,pitch[i].duration,pt,pr);break;
          }
          break;
      }

      case 320:
      {
          switch (pitch[i].finger) {
          case 1:
              Arm_control(dot.value_down_pose2(),pitch[i].finger,pitch[i].duration,pt,pr);break;

          default:Arm_control(dot.value_down_pose1(),2,pitch[i].duration,pt,pr);break;

          }
          break;
      }

      case 310:
      {
              Arm_control(dot.value_down_pose1(),1,pitch[i].duration,pt,pr);break;
      }

      default:
          //Arm_control(dot.value_pose1(),4,0,pt,pr);
          std::cout<<"the pitch has not been initialized!"<<std::endl;
          break;
      }
  }


  return 0;
}










