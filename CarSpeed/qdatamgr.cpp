#include "qdatamgr.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>
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
    speed++;
    angel += 2;
    acceleration +=3;
    qDebug() << "update: " << "speed = " <<
                speed << ", angel = " << angel << ", acceleration = " << acceleration;
}
