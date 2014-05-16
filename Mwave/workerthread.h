#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

/////////////Included Files//////////////
#include <QtCore>

class workerThread : public QThread
{

public:
    workerThread();
    ~workerThread();

public slots:
    void run();
};

#endif // WORKERTHREAD_H
