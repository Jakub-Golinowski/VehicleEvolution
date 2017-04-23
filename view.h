#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include "qb2draw.h"
#include "model.h"


class View : public QWidget
{
    Q_OBJECT
public:

   View(Model * model, QB2Draw * drawer);

   Model * _model;
   QB2Draw * _drawer;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // VIEW_H
