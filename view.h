#ifndef VIEW_H
#define VIEW_H

#include <QWidget> 
#include <QFrame>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include "model.h"
#include "spawn.h"


class View : public QFrame
{
    Q_OBJECT
public:

   View(Model * model);
   View();

   void setModel(Model * model);

   Model * model_;

   static const float32 DRAWING_SCALE;
   QSize minimumSizeHint() const override;
   QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VIEW_H
