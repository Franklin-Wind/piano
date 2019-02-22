#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "hand.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    hand Robotics_Hand;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Serial_Open_pushButton_clicked();

    void on_Serial_comboBox_currentIndexChanged(const QString &arg1);

    void on_Serial_Close_pushButton_clicked();

    void on_Hand_Open_pushButton_clicked();

    void on_Hand_Close_pushButton_clicked();

    void on_Read_Data_pushButton_clicked();

    void on_Send_Data_pushButton_clicked();

    void Aways_Read_Angle();

    void Delay_MSec_Suspend(unsigned int msec);


    void keyPressEvent(QKeyEvent *event); //键盘按下事件

    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
