#ifndef QDATAMGR_H
#define QDATAMGR_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>
class QDataMgr : public QObject
{
    Q_OBJECT
public:
    explicit QDataMgr(QObject *parent = nullptr);

signals:
public slots:
    void update();
public:
    Q_INVOKABLE int getSpeed();
    Q_INVOKABLE int getwheelAngel();
    Q_INVOKABLE int getAcceleration();
private:
    int speed;
    int angel;
    int acceleration;
    std::vector<int> info;
    QTimer *timer;
};
#endif // QDATAMGR_H
