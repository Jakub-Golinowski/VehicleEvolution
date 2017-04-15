#include "simworld.h"
#include <iostream>

const float SimWorld::BOX2D_QT_SCALE_FACTOR = 10;
const float32 SimWorld::BOX2D_TIMESTEP = 1.0f/60.0f;
const int32 SimWorld::BOX2D_VELOCITY_ITERATIONS = 6;
const int32 SimWorld::BOX2D_POSITION_ITERATIONS = 2;
const unsigned int SimWorld::QT_TIMER_PERIOD = 20;


SimWorld::SimWorld(unsigned long sizeX, unsigned long sizeY, float gravityX, float gravityY):
    scene(new QGraphicsScene), world(new b2World(b2Vec2(gravityX, gravityY)))
{
    scene->setSceneRect(0,0, sizeX, sizeY);
}

std::shared_ptr<QGraphicsScene> SimWorld::getScene() const
{
    return scene;
}

std::shared_ptr<b2World> SimWorld::getWorld() const
{
    return world;
}

void SimWorld::addObject(SimObject * newObject)
{
    objects.push_back(newObject);
}

void SimWorld::startSimulation()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(simulate()));
    timer.start(QT_TIMER_PERIOD);
}

void SimWorld::simulate()
{
    world->Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
    for( SimObject * object : objects){
        b2Vec2 position = object->body->GetPosition();
        float32 angle = object->body->GetAngle();
        object->item->setPos(position.x*BOX2D_QT_SCALE_FACTOR, scene->height()-position.y*BOX2D_QT_SCALE_FACTOR);
        object->item->setRotation(angle*180/M_PI);
        std::cout << position.x<< " " << position.y << " " << angle << std::endl;
    }

}
