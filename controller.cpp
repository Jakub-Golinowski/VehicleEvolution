#include "controller.h"

Controller::Controller(Model * model, View * view) : model_(model), view_(view)
{

}

void Controller::startSimulation(unsigned long interval)
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(simulateAndDraw()));
    timer_.start(interval);
}

void Controller::simulateAndDraw()
{
    model_->simulate();
    view_->repaint();
}
