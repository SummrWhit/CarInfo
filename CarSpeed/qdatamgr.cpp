#include "qdatamgr.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>
//#include "../../../../Project/Test/Student/student.h"
#include <vector>
#include "../can/canctrl.h"

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

void QDataMgr::update() {
    canctrlnode can;
    std::vector<int> info;
    can.getCanInfo(info);
    //canctrlnode::getCanInfo(info);
    //qDebug() << "student score = " << Student::getPoints();
    speed = info[0];
    angel = info[1];
    acceleration = info[2];
    qDebug() << "update: " << "speed = " <<
                speed << ", angel = " << angel << ", acceleration = " << acceleration;
}
