
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QThread>
#include <QTimer>
#include <Box2D/Box2D.h>

#include "simworld.h"
#include "simrect.h"
#include <iostream>

# define M_PI           3.14159265358979323846

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    float scaleFactor = 10.0f;

    unsigned long sceneWidth = 600;
    unsigned long sceneHeight = 800;

    SimWorld testSimWorld(sceneWidth,sceneHeight, 0.0f, -10.0f);

    QGraphicsView testView(testSimWorld.getScene().get());


    // Create static ground
    float groundBodyPosX = 10.0f;
    float groundBodyPosY = 2.0f;

    SimRect ground(&testSimWorld, 50.0f, 2.0f, groundBodyPosX, groundBodyPosY, 0.0f, 0.0f);

    float dynBodyPosX = 35.0f;
    float dynBodyPosY = 40.0f;

    SimRect dynamicBox(&testSimWorld, 2.0f, 2.0f, dynBodyPosX, dynBodyPosY, 1.0f, 0.3f);


    testView.setFixedSize(sceneWidth,sceneHeight);
    testView.show();


    // Simulating the world

    testSimWorld.startSimulation();

    return a.exec();


}
