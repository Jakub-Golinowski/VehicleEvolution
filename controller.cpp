#include "controller.h"

Controller::Controller(Model * model, View * view) : _model(model), _view(view)
{

}

void Controller::startSimulation(unsigned long interval)
{
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(simulateAndDraw()));
    timer->start(interval);
}

void Controller::simulateAndDraw()
{
    _model->simulate();
    _view->repaint();
}
