
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
#include <memory>

# define M_PI           3.14159265358979323846

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    vector<unique_ptr<SimRect>> v;

    float scaleFactor = 10.0f;

    unsigned long sceneWidth = 600;
    unsigned long sceneHeight = 800;

    SimWorld testSimWorld(sceneWidth,sceneHeight, 0.0f, -10.0f);

    QGraphicsView testView(testSimWorld.getScene().get());


    // Create static ground
    float groundBodyPosX = 10.0f;
    float groundBodyPosY = 2.0f;

    SimRect ground(&testSimWorld, 50.0f, 2.0f, groundBodyPosX,
                        groundBodyPosY, 0.0f, 1.0f, b2_staticBody,
                        0.0f);

    float dynBodyPosX = 10.0f;
    float dynBodyPosY = 40.0f;

//    unique_ptr<SimRect>(new SimRect(&testSimWorld, 2.0f, 2.0f, dynBodyPosX,
//                                    dynBodyPosY, 1.0f, 0.3f, b2_dynamicBody,
//                                   60.0f));

    v.push_back(unique_ptr<SimRect>(new SimRect(&testSimWorld, 2.0f, 2.0f, dynBodyPosX+8,
                                    dynBodyPosY, 1.0f, 0.3f, b2_dynamicBody, 45.0f)));

    v.push_back(unique_ptr<SimRect>(new SimRect(&testSimWorld, 5.0f, 2.0f, dynBodyPosX,
                                    dynBodyPosY+20, 1.0f, 0.3f, b2_dynamicBody, 45.0f)));

    v.push_back(unique_ptr<SimRect>(new SimRect(&testSimWorld, 2.0f, 8.0f, dynBodyPosX+7,
                                    dynBodyPosY+15, 1.0f, 0.3f, b2_dynamicBody, 45.0f)));

    v.push_back(unique_ptr<SimRect>(new SimRect(&testSimWorld, 2.0f, 2.0f, dynBodyPosX,
                                    dynBodyPosY-10, 1.0f, 0.3f, b2_dynamicBody, 0.0f)));

    v.push_back(unique_ptr<SimRect>(new SimRect(&testSimWorld, 3.0f, 5.0f, dynBodyPosX+4,
                                    dynBodyPosY+5, 1.0f, 0.3f, b2_dynamicBody, 45.0f)));

    v.push_back(unique_ptr<SimRect>(new SimRect(&testSimWorld, 2.0f, 2.0f, dynBodyPosX,
                                    dynBodyPosY-10, 1.0f, 0.3f, b2_dynamicBody, 25.0f)));



    testView.setFixedSize(sceneWidth,sceneHeight);
    testView.show();


    // Simulating the world

    testSimWorld.startSimulation();

    return a.exec();


}
