#ifndef QMYPC_H
#define QMYPC_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>

class QMyPC : public QObject
{
    Q_OBJECT

public:
    explicit QMyPC(QObject *parent = nullptr);

signals:

public slots:
    void update();

public:
    Q_INVOKABLE double getXPos();
    Q_INVOKABLE double getYPos();
    Q_INVOKABLE double getZPos();

private:
    double xPos;
    double yPos;
    double zPos;
    QTimer *timer;
};

#endif // QMYPC_H
