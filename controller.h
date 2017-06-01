#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTimer>
#include "model.h"
#include "view.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(Model * model, View * view);

    void startSimulation(unsigned long interval);

private:
    Model  * model_;
    View  * view_;
    QTimer timer_;

public slots:
    void simulateAndDraw();
};

#endif // CONTROLLER_H
