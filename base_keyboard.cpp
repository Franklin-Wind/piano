#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <thread>
#include "agv_msgs/SerialFrame.h"

#define KEYCODE_A 0x61
#define KEYCODE_B 0x62
#define KEYCODE_F 0x66
#define KEYCODE_D 0x64
#define KEYCODE_S 0x73
#define KEYCODE_W 0x77
#define KEYCODE_Q 0x71
#define KEYCODE_E 0x65
#define KEYCODE_R 0x72
#define KEYCODE_T 0x74
#define KEYCODE_Y 0x85
#define KEYCODE_G 0x67
#define KEYCODE_H 0x68




#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_F_CAP 0x46
#define KEYCODE_W_CAP 0x57
#define KEYCODE_Q_CAP 0x51
#define KEYCODE_E_CAP 0x45
#define KEYCODE_R_CAP 0x52



#define DAMP 0.05
#define ACC_STEP 0.01

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

class TeleopBaseKeyboard
{
private:
      ros::Publisher write_pub_;

      ros::NodeHandle n_;
      //std::thread * rt_damp_thread_;

public:
    void init()
    {

         write_pub_ = n_.advertise<agv_msgs::SerialFrame>("serial_write", 1000, true);     //定义一个发布对象，发布到serial_write话题
         //rt_damp_thread_ = new std::thread(boost::bind(&TeleopBaseKeyboard::dampThread, this));  //duo xian cheng
    }

    void dampThread();

    ~TeleopBaseKeyboard()   { }
    void keyboardLoop();
    int Com_Hands_AngleSet1(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6);
    int Com_Hands_AngleSet2(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6);
    int Com_Hands_AngleSet3();

};

int TeleopBaseKeyboard::Com_Hands_AngleSet1(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6)
{

           agv_msgs::SerialFrame frame;
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

            return 1;
}

//自动回弹手指控制函数
int TeleopBaseKeyboard::Com_Hands_AngleSet2(int dat1, int dat2, int dat3, int dat4, int dat5, int dat6)
{

           agv_msgs::SerialFrame frame;
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
            Com_Hands_AngleSet3();

            return 1;
}
int TeleopBaseKeyboard::Com_Hands_AngleSet3()   //回弹手指函数
{
   agv_msgs::SerialFrame frame;
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





int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
    tcsetattr(kfd, TCSANOW, &cooked);
    exit(0);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "base_keyboard");

    TeleopBaseKeyboard tbk;
    tbk.init();

    signal(SIGINT,quit);

    tbk.keyboardLoop();

    return(0);
}



void TeleopBaseKeyboard::keyboardLoop()
{
    int x,y,z,t,u,v;

    /*************设置初始位置的各个数值*/
    x=1600;y=1400;z=1500;t=1580;u=0;v=0;
    /*************/

    char c;
    bool dirty=false;

    // get the console in raw mode
    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    // Setting a new line, then end of file
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);


    puts("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    puts("'asdf||qwer||QE' to control the hand");
    Com_Hands_AngleSet1(x,y,z,t,u,v);  //初始手指位置
    ROS_INFO("%d %d %d %d %d %d",x,y,z,t,u,v);


    for(;;)
    {
        // get the next event from the keyboard
        if(read(kfd, &c, 1) < 0)
        {
            perror("read():");
            exit(-1);
        }
        switch(c)     //手指位置调节 Q、W、E、R  和A、S、D、F分别为弯曲和伸开
        {
        case KEYCODE_Q:
            if(x>0)
                x=x-20;
            else
               x=0;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_W:
            if(y>0)
                y=y-20;
            else
               y=0;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_E:
            if(z>0)
                z=z-20;
            else
               z=0;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_R:
            if(t>0)
                t=t-20;
            else
               t=0;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_T:
            if(u>0)
                u=u-20;
            else
               u=0;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_B:
            if(v>0)
                v=v-20;
            else
               v=0;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_G:
            if(u<2000)
                u=u+20;
            else
               u=2000;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_H:
            if(v<2000)
                v=v+20;
            else
               v=2000;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_A:
            if(x<2000)
                x=x+20;
            else
               x=2000;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_S:
            if(y<2000)
                y=y+20;
            else
               y=2000;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_D:
            if(z<2000)
                z=z+20;
            else
               z=2000;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;
        case KEYCODE_F:
            if(t<2000)
                t=t+20;
            else
               t=2000;
            Com_Hands_AngleSet1(x,y,z,t,u,v);
            break;

        case KEYCODE_Q_CAP:
            Com_Hands_AngleSet2(1400,1400,1500,1580,0,0);   //1600;y=1400;z=1500;t=1580
            break;
        case KEYCODE_W_CAP:
            Com_Hands_AngleSet2(1600,1160,1500,1580,0,0);
            break;
        case KEYCODE_E_CAP:
            Com_Hands_AngleSet2(1600,1400,1200,1580,0,0);
            break;
        case KEYCODE_R_CAP:
            Com_Hands_AngleSet2(1600,1400,1500,1300,0,0);
            break;
        }
        ROS_INFO("%d %d %d %d %d %d",x,y,z,t,u,v);

    }
}

void TeleopBaseKeyboard::dampThread() {
    while (ros::ok()) {
//        if (pressd.linear.x == 0) {
//            acc.linear.x = 0;
//        }
//        if (pressd.linear.y == 0) {
//            acc.linear.y = 0;
//        }
//        if (pressd.angular.z == 0) {
//            acc.angular.z = 0;
//        }
//        if (cmd.linear.x > 0) damp.linear.x = -DAMP;
//        else if (cmd.linear.x < 0) damp.linear.x = DAMP;
//        else damp.linear.x = 0.;

//        if (cmd.linear.y > 0) damp.linear.y = -DAMP;
//        else if (cmd.linear.y < 0) damp.linear.y = DAMP;
//        else damp.linear.y = 0.;

//        if (cmd.angular.z > 0) damp.angular.z = -DAMP;
//        else if (cmd.angular.z < 0) damp.angular.z = DAMP;
//        else damp.angular.z = 0.;

//        cmd.linear.x += (acc.linear.x + damp.linear.x);
//        cmd.linear.y += (acc.linear.y + damp.linear.y);
//        cmd.angular.z += (acc.angular.z + damp.angular.z);

//        if (cmd.linear.x > 0.5) cmd.linear.x = 0.5;
//        if (cmd.linear.x < -0.5) cmd.linear.x = -0.5;

//        if (cmd.linear.y > 0.5) cmd.linear.y = 0.5;
//        if (cmd.linear.y < -0.5) cmd.linear.y = -0.5;

//        if (cmd.angular.z > 0.5) cmd.angular.z = 0.5;
//        if (cmd.angular.z < -0.5) cmd.angular.z = -0.5;

//        pressd.linear.x = 0;
//        pressd.linear.y = 0;
//        pressd.angular.z = 0;

//        vel_pub_.publish(cmd);
//        ros::Duration(ros::Rate(10.)).sleep();
    }
}
