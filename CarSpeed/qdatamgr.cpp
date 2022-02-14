#include "qdatamgr.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>
#include "../../../../Project/Test/Student/student.h"
#include <vector>
#include "../../carSpeed/can/canctrl.h"
#include "../../../../Project/nebula/userapi/Reciever.hpp"

using namespace allride_ai_com;

struct car_info {
    float speed;
    float acc;
    float steer;
};
int i = 0;

QDataMgr::QDataMgr(QObject *parent) : QObject(parent)
{
    speed = 0;
    angel = 0;
    acceleration = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

int QDataMgr::getSpeed() {
    qDebug() << "speed: " << speed;
    /*FIXME: avoid car speed > 200 and wheel angel need catch abnormal*/
    return speed;
}

int QDataMgr::getwheelAngel() {
    return angel;
}
int QDataMgr::getAcceleration() {
    return acceleration;
}
void * callBack(const void* data, int len, unsigned long long timeStamp, void* arg) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct car_info* pdata = (struct car_info*)data;
    cout <<"timestamp:" << timeStamp<<" delay:("<<(1000000*tv.tv_sec+tv.tv_usec-timeStamp)
            <<"us) length:("<<len<<"bytes)   data:\n" <<pdata[i++].acc<<"\n"<<endl;
    return arg;
}
void QDataMgr::update() {
    RecieverPtr recv = new Reciever("whr", 200, callBack);
    int count = 0;
    //while (count++ < 10000000)
    {
        recv->spin();
    }
    qDebug() << "student score = " << Student::getPoints();
    speed++;// = info[0];
    angel+=2;// = info[1];
    acceleration+=3;// = info[2];
    qDebug() << "update: " << "speed = " <<
                speed << ", angel = " << angel << ", acceleration = " << acceleration;
}
