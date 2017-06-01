#ifndef VIEW_H
#define VIEW_H

#include <QWidget> 
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include "model.h"
#include "spawn.h"


class View : public QWidget
{
    Q_OBJECT
public:

   View(Model * model);
   View();

   Model * model_;

   static const float32 DRAWING_SCALE;
   QSize minimumSizeHint() const override;
   QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VIEW_H
