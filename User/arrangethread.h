#ifndef ARRANGETHREAD_H
#define ARRANGETHREAD_H
#include <QThread>
#include <QMutex>
using namespace std;
class arrangeThread : public QThread
{
    Q_OBJECT

public:
    arrangeThread(QObject* par);
    ~arrangeThread();
    void run();
    void setID(string name,string pass);
public slots:
    void stopImmediately();
signals:
    void send(QString s);
private:
    QMutex m_lock;
    bool m_isCanRun;
    string username;
    string password;
};

#endif // ARRANGETHREAD_H
