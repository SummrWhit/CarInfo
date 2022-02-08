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
    connect(timer, SIGNAL(timeout()), this, SLOT(show()));
    timer->start(1000);
}

int QMyPC::show() {
    qDebug() << "whr, show func";
}
