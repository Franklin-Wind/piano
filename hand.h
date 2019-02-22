#ifndef HAND_H
#define HAND_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QDebug>
#include <synchapi.h>


class hand
{
public:
    hand();
    QSerialPort serial;
    QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
    QSerialPortInfo info;
    uint16_t Set_Hand_data1,Set_Hand_data2,Set_Hand_data3,Set_Hand_data4,Set_Hand_data5,Set_Hand_data6=0; //设置角度
    uint16_t current_angle1,current_angle2,current_angle3,current_angle4,current_angle5,current_angle6=0;  //当前各关节角度值
#define  Hands_ID  1


#define FRAME_HEAD1  				0xEB
#define FRAME_HEAD2  				0x90
#define FRAME_HEAD1_RT  			0xEE
#define FRAME_HEAD2_RT  			0x16

#define CMD_MC_SET_DRVALL_SEEKPOS 							0x50
#define CMD_MC_SET_DRVALL_SPEED 							0x51
#define CMD_MC_SET_DRVALL_YBP_THRESHOLD						0x52
#define CMD_MC_SET_DRVALL_SEEKANGLE							0x53
#define CMD_MC_SET_DRVALL_SEEKANGLE_GYH						0x54
#define CMD_MC_SET_DJ_TURN									0x55


#define CMD_MC_READ_DRVALL_SEEKPOS 							0xD0
#define CMD_MC_READ_DRVALL_CURPOS 							0xD1
#define CMD_MC_READ_DRVALL_SPEED 							0xD2
#define CMD_MC_READ_DRVALL_YBP_THRESHOLD					0xD3
#define CMD_MC_READ_DRVALL_YBP_RAWDATA						0xD4
#define CMD_MC_READ_DRVALL_SEEKANGLE 						0xD5
#define CMD_MC_READ_DRVALL_CURANGLE 						0xD6
#define CMD_MC_READ_DRVALL_SEEKGYHANGLE 					0xD7
#define CMD_MC_READ_DJ_TURN									0xD8
#define CMD_MC_READ_DRVALL_CURANGLE_GYH						0xD9
#define CMD_MC_READ_BIT										0xDA


#define CMD_MC_PARA_SAVE 											0x01
#define CMD_MC_PARA_READ 											0x02
#define CMD_MC_PARA_USED_DEF										0x03
#define CMD_MC_PARA_ID_SET											0x04
#define CMD_MC_MOVE_K_SET_CURPOS_IN_CMAP							0x05
#define CMD_MC_MOVE_K_SHOW											0x06
#define CMD_MC_MOVE_K_SHOW_ASDEFAULT								0x07

char CMD1_MC_Array[50] = { 0 };
char Com1_RecBuf[50] = { 0 };
char CMD1_MC_REC_Array[50] = { 0 };
int Send1_Len = 0;
int Rec1_Len = 0;
int Com_Hands_AngleSet1(int data1, int data2, int data3, int data4, int data5, int data6);
int Com_Hands_AngleSet2();
QByteArray Receive_Buff;
int Read_Hands_Angle();


};

#endif // HAND_H
