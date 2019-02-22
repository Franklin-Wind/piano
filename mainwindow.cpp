#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QDebug>
#include <synchapi.h>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include<QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QTimer *myTime;
//    myTime=new QTimer();
//    myTime->setInterval(2000);
//    connect(myTime,SIGNAL(timeout()),this,SLOT(Aways_Read_Angle()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Serial_Open_pushButton_clicked()
{
    connect(&Robotics_Hand.serial,SIGNAL(readyRead()),this,SLOT(serialRead()));   //连接槽
    ui->Serial_comboBox->clear();
    //获取计算机上所有串口并添加到comboBox中
    if(Robotics_Hand.infos.isEmpty())
    {
        ui->Serial_comboBox->addItem(u8"无串口");
        qDebug()<<"打开失败";
        return;
    }
    foreach (Robotics_Hand.info, Robotics_Hand.infos)
    {
        ui->Serial_comboBox->addItem(Robotics_Hand.info.portName());
        qDebug() << Robotics_Hand.info.portName();

    }
}

void MainWindow::on_Serial_comboBox_currentIndexChanged(const QString &arg1)
{
        int i = 0;
        foreach (Robotics_Hand.info, Robotics_Hand.infos) {
            if(Robotics_Hand.info.portName() == arg1) break;
            i++;
        }
        if(i != Robotics_Hand.infos.size ()){//can find
            ui->Serial_label->setText(u8"串口打开成功");
            Robotics_Hand.serial.close();
            Robotics_Hand.serial.setPort(Robotics_Hand.info);
            Robotics_Hand.serial.open(QIODevice::ReadWrite);          //读写打开
            Robotics_Hand.serial.setBaudRate(QSerialPort::Baud115200);  //波特率
            Robotics_Hand.serial.setDataBits(QSerialPort::Data8);     //数据位
            Robotics_Hand.serial.setParity(QSerialPort::NoParity);    //无奇偶校验
            Robotics_Hand.serial.setStopBits(QSerialPort::OneStop);   //1停止位
            Robotics_Hand.serial.setFlowControl(QSerialPort::NoFlowControl);  //无控制
        }else{
            Robotics_Hand.serial.close();
            ui->Serial_label->setText(u8"串口打开失败");
        }
}


void MainWindow::on_Serial_Close_pushButton_clicked()
{
    ui->Serial_comboBox->clear();
    Robotics_Hand.serial.close();
}


void MainWindow::on_Hand_Open_pushButton_clicked()
{
Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
}

void MainWindow::on_Hand_Close_pushButton_clicked()
{
Robotics_Hand.Com_Hands_AngleSet1(0,0,0,0,0,0);
}

void MainWindow::on_Read_Data_pushButton_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Aways_Read_Angle()));
    timer->start(1000);

//    Robotics_Hand.Read_Hands_Angle();
//    ui->Read_Data_textEdit->append(Robotics_Hand.Receive_Buff.toHex());
//    ui->Current_Angle1_lineEdit->setText(QString::number(Robotics_Hand.current_angle1));
//    ui->Current_Angle2_lineEdit->setText(QString::number(Robotics_Hand.current_angle2));
//    ui->Current_Angle3_lineEdit->setText(QString::number(Robotics_Hand.current_angle3));
//    ui->Current_Angle4_lineEdit->setText(QString::number(Robotics_Hand.current_angle4));
//    ui->Current_Angle5_lineEdit->setText(QString::number(Robotics_Hand.current_angle5));
//    ui->Current_Angle6_lineEdit->setText(QString::number(Robotics_Hand.current_angle6));
}

void MainWindow::on_Send_Data_pushButton_clicked()
{
//    QString angle1=ui->Current_Angle1_textEdit->toPlainText();
//    Robotics_Hand.Set_Hand_data1=angle1.toInt();
//    QString angle2=ui->Current_Angle2_textEdit->toPlainText();
//    Robotics_Hand.Set_Hand_data2=angle2.toInt();
//    QString angle3=ui->Current_Angle3_textEdit->toPlainText();
//    Robotics_Hand.Set_Hand_data3=angle3.toInt();
//    QString angle4=ui->Current_Angle4_textEdit->toPlainText();
//    Robotics_Hand.Set_Hand_data4=angle4.toInt();
//    QString angle5=ui->Current_Angle5_textEdit->toPlainText();
//    Robotics_Hand.Set_Hand_data5=angle5.toInt();
//    QString angle6=ui->Current_Angle6_textEdit->toPlainText();
//    Robotics_Hand.Set_Hand_data6=angle6.toInt();
//    Robotics_Hand.Com_Hands_AngleSet2();
//    Robotics_Hand.Read_Hands_Angle();
//    ui->Current_Angle1_lineEdit->setText(QString::number(Robotics_Hand.current_angle1));
//    ui->Current_Angle2_lineEdit->setText(QString::number(Robotics_Hand.current_angle2));
//    ui->Current_Angle3_lineEdit->setText(QString::number(Robotics_Hand.current_angle3));
//    ui->Current_Angle4_lineEdit->setText(QString::number(Robotics_Hand.current_angle4));
//    ui->Current_Angle5_lineEdit->setText(QString::number(Robotics_Hand.current_angle5));
//    ui->Current_Angle6_lineEdit->setText(QString::number(Robotics_Hand.current_angle6));

//    Robotics_Hand.Com_Hands_AngleSet1(0,2000,2000,0,0,0);
//    Delay_MSec_Suspend(1000);
    qDebug() << "111";
    Robotics_Hand.Com_Hands_AngleSet1(0,0,0,0,0,0);
    Delay_MSec_Suspend(500);  //缓冲时间
    qDebug() << "222";
    Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,0,0);

    //while(!((Robotics_Hand.current_angle1<250)&&(Robotics_Hand.current_angle2<250)&&(Robotics_Hand.current_angle3<250)&&(Robotics_Hand.current_angle4<250)&&(Robotics_Hand.current_angle5<250)&&(Robotics_Hand.current_angle6<250)));

}

void MainWindow::Aways_Read_Angle()
{

    qDebug()<<"多线程启动:";
    Robotics_Hand.Read_Hands_Angle();
    ui->Read_Data_textEdit->append(Robotics_Hand.Receive_Buff.toHex());
    ui->Current_Angle1_lineEdit->setText(QString::number(Robotics_Hand.current_angle1));
    ui->Current_Angle2_lineEdit->setText(QString::number(Robotics_Hand.current_angle2));
    ui->Current_Angle3_lineEdit->setText(QString::number(Robotics_Hand.current_angle3));
    ui->Current_Angle4_lineEdit->setText(QString::number(Robotics_Hand.current_angle4));
    ui->Current_Angle5_lineEdit->setText(QString::number(Robotics_Hand.current_angle5));
    ui->Current_Angle6_lineEdit->setText(QString::number(Robotics_Hand.current_angle6));
    Robotics_Hand.Receive_Buff.clear();

}

void MainWindow::Delay_MSec_Suspend(unsigned int msec)
{

    QTime _Timer = QTime::currentTime();

    QTime _NowTimer;
    do{
              _NowTimer=QTime::currentTime();
    }while (_Timer.msecsTo(_NowTimer)<=msec);

}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{

   if(ev->key() == Qt::Key_O)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
   }

   if(ev->key() == Qt::Key_C)
   {
      Robotics_Hand.Com_Hands_AngleSet1(0,0,0,0,0,0);


   }

   if(ev->key() == Qt::Key_Q)
   {
      Robotics_Hand.Com_Hands_AngleSet1(1000,2000,2000,2000,2000,2000);
      Delay_MSec_Suspend(50);
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
   }

   if(ev->key() == Qt::Key_W)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,1000,2000,2000,2000,2000);
      Delay_MSec_Suspend(50);
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
   }
   if(ev->key() == Qt::Key_E)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,1000,2000,2000,2000);
      Delay_MSec_Suspend(50);
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
   }
   if(ev->key() == Qt::Key_R)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,1000,2000,2000);
      Delay_MSec_Suspend(50);
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
   }

   if(ev->key() == Qt::Key_A)
   {
      Robotics_Hand.Com_Hands_AngleSet1(1000,2000,2000,2000,2000,2000);
   }

   if(ev->key() == Qt::Key_S)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,1000,2000,2000,2000,2000);

   }
   if(ev->key() == Qt::Key_D)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,1000,2000,2000,2000);

   }
   if(ev->key() == Qt::Key_F)
   {
      Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,1000,2000,2000);

   }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event) //键盘松开事件
{
    if(event->key() == Qt::Key_A)
    {
        Delay_MSec_Suspend(50);
        Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);
    }

    if(event->key() == Qt::Key_S)
    {
        Delay_MSec_Suspend(50);
        Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);

    }
    if(event->key() == Qt::Key_D)
    {
        Delay_MSec_Suspend(50);
        Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);

    }
    if(event->key() == Qt::Key_F)
    {
        Delay_MSec_Suspend(50);
        Robotics_Hand.Com_Hands_AngleSet1(2000,2000,2000,2000,2000,2000);

    }



}



