#ifndef CHOOSETHREAD_H
#define CHOOSETHREAD_H

#include <QThread>
#include <QMutex>
#include <QDate>
class chooseThread : public QThread
{
    Q_OBJECT

public:
    chooseThread(QObject* par);
    ~chooseThread();
    void run();
    void setDate(QDate a,QDate b);
    QDate startd;
    QDate endd;
public slots:
    void stopImmediately();
signals:
    void send(int count);
private:
    QMutex m_lock;
    bool m_isCanRun;
    int count;
};


#endif // CHOOSETHREAD_H
