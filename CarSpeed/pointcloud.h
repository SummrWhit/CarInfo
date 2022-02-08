#ifndef POINTCLOUD_H
#define POINTCLOUD_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTimer>

class pointcloud : public QObject
{
    Q_OBJECT
public:
    explicit pointcloud(QObject *parent = nullptr);

public slots:
    int show();

private:
    QTimer *timer;
};

#endif // POINTCLOUD_H
