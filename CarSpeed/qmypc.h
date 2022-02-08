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
    int show();
private:
    QTimer *timer;
};

#endif // QMYPC_H
