#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controller
{
public:
    Controller(Model& model, View& view);

private:

    Model _model;
    View _view;
};

#endif // CONTROLLER_H
