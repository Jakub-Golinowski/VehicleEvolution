#ifndef SIMWORLD_H
#define SIMWORLD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <Box2D/Box2D.h>

#include "simobject.h"



// Class that combines b2World from Box2D and QGraphicsScene from QT.

class SimWorld : public QObject {
    Q_OBJECT
public:

    static const float BOX2D_QT_SCALE_FACTOR;

    SimWorld( unsigned long sizeX, unsigned long sizeY, float gravityX, float gravityY);

    std::shared_ptr<QGraphicsScene> getScene() const;

    std::shared_ptr<b2World> getWorld() const;

    void addObject(SimObject * newObject);

    void startSimulation();

public slots:
    void simulate();

private:

    static const float32 BOX2D_TIMESTEP;
    static const int32 BOX2D_VELOCITY_ITERATIONS;
    static const int32 BOX2D_POSITION_ITERATIONS;
    static const unsigned int QT_TIMER_PERIOD;

    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<b2World> world;
    std::vector<SimObject*> objects;

    QTimer timer;
};

#endif // SIMWORLD_H
