#include "controller.h"

Controller::Controller(Model * model, View * view) : model_(model), view_(view)
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
    model_->simulate();
    view_->repaint();
}
