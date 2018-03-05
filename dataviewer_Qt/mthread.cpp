#include "mthread.h"
#include <QtCore>
#include <QDebug>

mThread::mThread()
{

}

void mThread::run()
{
    QProcess *process = new QProcess(this);
    if(this->display)
    {
        char* command;
        QByteArray com = file.toLatin1();
        command = com.data();
        system(command);
    }
    else
    {
        process->start(file);
    }

/*
    char* command;
    QByteArray com = file.toLatin1();
    command = com.data();
    system(command);
*/
/*
    switch (exenum) {
    case 1:
        this->file = "dynamicPath.exe";
        process->start(file);
        break;
    case 2:
        this->file = "display_ACCL.exe";
        process->start(file);
        break;
    case 3:
        this->file = "display_GYRO.exe";
        process->start(file);
        break;
    case 4:
        //this->file = "display_GPS.exe";
        this->file = "display.exe";
        process->start(file);
        break;
    case 5:
        //this->file = "display.exe";
        this->file = "display_GPS.exe";
        process->start(file);
        break;
    default:
        break;
    }
*/
}
