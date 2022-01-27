#include "qdatamgr.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>
QDataMgr::QDataMgr(QObject *parent) : QObject(parent)
{
    number = 2;
    timer = new QTimer(this);
    //timer->stop();
    //timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

int QDataMgr::info() {
    qDebug() << "number: " << number;
    return number;
}

void QDataMgr::update() {
    qDebug() << "update: " << number;
    number++;
}
