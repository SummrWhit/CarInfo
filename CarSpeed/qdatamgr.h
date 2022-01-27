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
    Q_PROPERTY(int number READ rtxt WRITE settxt NOTIFY txtchanged)
public:
    explicit QDataMgr(QObject *parent = nullptr);
    int rtxt() const {return number;}
    void settxt(int s) {number = s; emit txtchanged();}

signals:
    void txtchanged();
public slots:
    void update();
public:
    Q_INVOKABLE int info();
private:
    int number;
    QTimer *timer;
};
#endif // QDATAMGR_H
