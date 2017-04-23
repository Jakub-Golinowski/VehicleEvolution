#include "view.h"




View::View(Model * model, QB2Draw * drawer)
    :_model(model), _drawer(drawer)
{

}

void View::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    _drawer->setPainter(&p);
    _model->DrawModelData();

    p.end();
}
