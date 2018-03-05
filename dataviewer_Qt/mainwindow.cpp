#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_display_clicked()
{/*
    mThread thread_map;
    thread_map.exenum = 1;
    mThread thread_accl;
    thread_accl.exenum = 2;
    mThread thread_gyro;
    thread_gyro.exenum = 3;
    mThread thread_gps;
    thread_gps.exenum = 4;
    mThread thread_video;
    thread_video.exenum = 5;
    mThread thread_test;
*/

    mThread thread_map;
    thread_map.file = "dynamicPath"+this->filename+".exe";
    thread_map.display = false;

    mThread thread_accl;
    thread_accl.file = "display_ACCL.exe";
    thread_accl.display = false;

    mThread thread_gyro;
    thread_gyro.file = "display_GYRO.exe";
    thread_gyro.display = false;

    mThread thread_gps;
    thread_gps.file = "display_GPS"+this->filename+".exe";
    mThread thread_video;
    thread_gps.display = false;

    thread_video.file = "display.exe " + this->filename + ".mp4";
    mThread thread_test;
    thread_video.display = true;

    thread_map.start();
    thread_accl.start();
    thread_gyro.start();
    thread_gps.start();
    thread_video.start();
    thread_test.start();

}

void MainWindow::on_parse_clicked()
{
    this->filename = ui->lineEdit->text();
    QString str = "gpmf-parser.exe " + this->filename + ".mp4";
    qDebug()<<str;
    char* command;
    QByteArray com = str.toLatin1();
    command = com.data();
    system(command);
}
