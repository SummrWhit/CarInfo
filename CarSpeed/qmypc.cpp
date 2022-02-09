#include "qmypc.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>

QMyPC::QMyPC(QObject *parent) : QObject(parent)
{
    qDebug() << "whr, construct func";
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

void QMyPC::update() {
    qDebug() << "whr, show func";
    //receiver and update lidar data

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


