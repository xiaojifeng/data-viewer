#ifndef MTHREAD_H
#define MTHREAD_H
#include <QtCore>

using namespace std;

class mThread : public QThread
{
public:
    mThread();
    void run();
    int exenum;
    QString file;
    bool display;
};

#endif // MTHREAD_H
