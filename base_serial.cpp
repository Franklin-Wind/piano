#include <ros/ros.h>
#include <serial/serial.h>  //ROS已经内置了的串口包
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include "base_serial.h"

#include "agv_msgs/SerialFrame.h"

#define FRAME_HEAD1  				0xEB
#define FRAME_HEAD2  				0x90


serial::Serial ser; //声明串口对象

agv_msgs::SerialFrame frame; //read data from robot




//回调函数
void write_callback(const agv_msgs::SerialFrameConstPtr &msg)
{
     std::cout << "*****************************8" << std::endl;
   std::cout << "into write_back()" << std::endl;
  // ROS_INFO("frame.data0:0x%X ", msg->data[0]);

/**********************************************************************************************/
    int i = 0;
    int j=0;
    //uint8_t XOR = 0;
    uint8_t SUM = 0;
    std::vector<uint8_t> data;
    data.resize(msg->len + 5);
    ROS_DEBUG("head1: 0x%X,head2: 0x%X,ID: 0x%X,len: 0x%X, cmd: 0x%X,  data: ", msg->head1, msg->head2, msg->id, msg->len, msg->cmd);
//     for(int i = 0; i < msg->len + 5; i++)
//     {
//        ROS_DEBUG("0x%X ", msg->data[i]);
//     }

    data[i] = msg->head1; // 0
    i++;

    data[i] = msg->head2; // 1
    i++;

    data[i] = msg->id; // 2
    i++;
    SUM=SUM+data[i];

    data[i] = msg->len;  // 3
    i++;
    SUM=SUM+data[i];


    data[i] = msg->cmd; // 4
    i++;
    SUM=SUM+data[i];


    while(i < msg->len+5 ) { //5
        data[i] = msg->data[i-5];
        SUM += data[i];
        i++;
    }
    //data[i] = SUM & 0xFF;


    ser.write(data);

/*************************************************************************************************************/
}


int main (int argc, char** argv)
{
    //初始化节点
    ros::init(argc, argv, "base_serial_node");
    //声明节点句柄
    ros::NodeHandle nh;

    //订阅主题，并配置回调函数
    ros::Subscriber write_sub = nh.subscribe("serial_write", 1000, write_callback);

    //发布主题
    //ros::Publisher receive_pub = nh.advertise<agv_msgs::SerialFrame>("serial_receive", 1000);

    try
    {
    //设置串口属性，并打开串口
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    //检测串口是否已经打开，并给出提示信息
    if(ser.isOpen())
    {
        ROS_INFO_STREAM("Serial Port initialized");
    }
    else
    {
        return -1;
    }

        ros::spin();


}
