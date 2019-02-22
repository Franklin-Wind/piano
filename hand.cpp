#include "hand.h"

hand::hand()
{

}

int hand::Com_Hands_AngleSet1(int data1, int data2, int data3, int data4, int data5, int data6)
{
    qDebug() << "*******************" ;
    qDebug() << "Com_Hands_AngleSet" ;
    int st = 0;
    short int temp_seekpos_array[6] = { 0 };
    int i = 0;
    unsigned int check_sum = 0;


    CMD1_MC_Array[0] = FRAME_HEAD1;
    CMD1_MC_Array[1] = FRAME_HEAD2;
    CMD1_MC_Array[2] = Hands_ID;
    CMD1_MC_Array[3] = 0x0D;
    CMD1_MC_Array[4] = CMD_MC_SET_DRVALL_SEEKPOS;
    //--------------------------------------------------------------
    temp_seekpos_array[0] = data1;
    temp_seekpos_array[1] = data2;
    temp_seekpos_array[2] = data3;
    temp_seekpos_array[3] = data4;
    temp_seekpos_array[4] = data5;
    temp_seekpos_array[5] = data6;
    for (i = 0; i < 6; i++)
    {
        CMD1_MC_Array[i * 2 + 5] = (temp_seekpos_array[i] & 0xFF);
        CMD1_MC_Array[i * 2 + 6] = ((temp_seekpos_array[i] >> 8) & 0xFF);
    }
    for (i = 2; i < (CMD1_MC_Array[3]+5-1); i++)
    {
        check_sum = check_sum + CMD1_MC_Array[i];
    }
    CMD1_MC_Array[CMD1_MC_Array[3]+5-1] = check_sum & 0xFF;

    serial.write(CMD1_MC_Array, (CMD1_MC_Array[3] + 5));
    //st = Uart1_Send_Array((CMD1_MC_Array[3] + 5));

    QByteArray data;
    data=CMD1_MC_Array;
    qDebug() << "data: " <<data.toHex();

    serial.waitForBytesWritten();
    return 1;
}

int hand::Com_Hands_AngleSet2()
{
    qDebug() << "*******************" ;
    qDebug() << "Com_Hands_AngleSet" ;
    int st = 0;
    short int temp_seekpos_array[6] = { 0 };
    int i = 0;
    unsigned int check_sum = 0;


    CMD1_MC_Array[0] = FRAME_HEAD1;
    CMD1_MC_Array[1] = FRAME_HEAD2;
    CMD1_MC_Array[2] = Hands_ID;
    CMD1_MC_Array[3] = 0x0D;
    CMD1_MC_Array[4] = CMD_MC_SET_DRVALL_SEEKPOS;
    //--------------------------------------------------------------
    temp_seekpos_array[0] = Set_Hand_data1;
    temp_seekpos_array[1] = Set_Hand_data2;
    temp_seekpos_array[2] = Set_Hand_data3;
    temp_seekpos_array[3] = Set_Hand_data4;
    temp_seekpos_array[4] = Set_Hand_data5;
    temp_seekpos_array[5] = Set_Hand_data6;
    for (i = 0; i < 6; i++)
    {
        CMD1_MC_Array[i * 2 + 5] = (temp_seekpos_array[i] & 0xFF);
        CMD1_MC_Array[i * 2 + 6] = ((temp_seekpos_array[i] >> 8) & 0xFF);
    }
    for (i = 2; i < (CMD1_MC_Array[3]+5-1); i++)
    {
        check_sum = check_sum + CMD1_MC_Array[i];
    }
    CMD1_MC_Array[CMD1_MC_Array[3]+5-1] = check_sum & 0xFF;
    serial.write(CMD1_MC_Array, (CMD1_MC_Array[3] + 5));


    QByteArray data;
    data=CMD1_MC_Array;
    qDebug() << "data: " <<data.toHex();

    serial.waitForBytesWritten();
    return 1;
}

int hand::Read_Hands_Angle()
{
    char array[6];
    int len;
    unsigned int check_sum = 0;

   array[0] = 0xEB;
   array[1] = 0x90;
   array[2] = 0x01;
   array[3] = 0x01;
   array[4] = 0xD1;
   array[5] = 0xD3;

   serial.write(array, 6);

   QByteArray buf;
   buf = serial.readAll();


   if(buf.isEmpty())
   {
       qDebug() << "empty " ;
       return 0;
   }

   if(buf[4]!=0xd1)
   {
       return 0;
       qDebug() << "不是读速度的指令 " ;
   }

   Receive_Buff=buf;

   qDebug() << "==========串口接收位置信息=========";
   qDebug() << "receive_data: " <<buf.toHex();

   len=buf[3];
   if (len<8)
   {
       qDebug() << "收到回复命令 " ;
       return 0;
   }

   for (int i = 2; i < len+5-1; i++)
   {
       check_sum = check_sum + buf[i];
   }

    qDebug() << "CHECK: " <<(check_sum& 0xFF);
   if (buf[len+5-1]==(check_sum & 0xFF))
   {
               qDebug() << "校验成功 ";

               current_angle1=(unsigned char)buf[6];
               current_angle1=current_angle1<<8;
               current_angle1|= (unsigned char)buf[5];
               if(current_angle1<0)current_angle1=0;
               if(current_angle1>2000)current_angle1=2000;
               qDebug() << "current_angle1= "<<current_angle1;

               current_angle2=(unsigned char)buf[8];
               current_angle2=current_angle2<<8;
               current_angle2|= (unsigned char)buf[7];
               if(current_angle2<0)current_angle2=0;
               if(current_angle2>2000)current_angle2=2000;
               qDebug() << "current_angle2= "<<current_angle2;

               current_angle3=(unsigned char)buf[10];
               current_angle3=current_angle3<<8;
               current_angle3|= (unsigned char)buf[9];
               if(current_angle3<0)current_angle3=0;
               if(current_angle3>2000)current_angle3=2000;
               qDebug() << "current_angle3= "<<current_angle3;

               current_angle4=(unsigned char)buf[12];
               current_angle4=current_angle4<<8;
               current_angle4|= (unsigned char)buf[11];
               if(current_angle4<0)current_angle4=0;
               if(current_angle4>2000)current_angle4=2000;
               qDebug() << "current_angle4= "<<current_angle4;

               current_angle5=(unsigned char)buf[14];
               current_angle5=current_angle5<<8;
               current_angle5|= (unsigned char)buf[13];
               if(current_angle5<0)current_angle5=0;
               if(current_angle5>2000)current_angle5=2000;
               qDebug() << "current_angle5= "<<current_angle5;

               current_angle6=(unsigned char)buf[16];
               current_angle6=current_angle6<<8;
               current_angle6|= (unsigned char)buf[15];
               if(current_angle6<0)current_angle6=0;
               if(current_angle6>2000)current_angle6=2000;
               qDebug() << "current_angle6= "<<current_angle6;

               return 1;

   }
   else qDebug() << "校验失败 ";

   return 0;

}
