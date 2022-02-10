#include "qmypc.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

QMyPC::QMyPC(QObject *parent) : QObject(parent)
{
    qDebug() << "whr, construct func";
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void QMyPC::update() {
    //qDebug() << "whr, show func";
    //receiver and update lidar data
    struct timespec ts;
    //printf("nano second is: %09ld\n", ts.tv_nsec);

    timespec_get(&ts, TIME_UTC);
    xPos = ts.tv_nsec % 500;
    qDebug() << "x = " << xPos;
    timespec_get(&ts, TIME_UTC);
    yPos = ts.tv_nsec % 500;
    qDebug() << "y = " << yPos;
    timespec_get(&ts, TIME_UTC);
    zPos = ts.tv_nsec % 500;
    qDebug() << "z = " << zPos;
}

double QMyPC::getXPos() {
    return xPos;
}

double QMyPC::getYPos() {
    return yPos;
}

double QMyPC::getZPos() {
    return zPos;
}


