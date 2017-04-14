
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QThread>
#include <QTimer>
#include <Box2D/Box2D.h>

#include "simworld.h"
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

    /* Create static body ground */

    // Box2D
    float groundBodyPosX = 10.0f;
    float groundBodyPosY = 2.0f;
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(groundBodyPosX, groundBodyPosY);

    b2Body * groundBody = testSimWorld.getWorld()->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(25.0f,2.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    // QGraphics
    QGraphicsRectItem groundRectangle;
    // First two parameters are setting the local origin point in the middle of the rectangle
    // so that it complies with Box2D coordinates. May be harder to implement with general polygons.
    groundRectangle.setRect(-250,-20, 500, 40);
    testSimWorld.getScene()->addItem(&groundRectangle);



    /* END_OF: Create static body ground */


    /* Create dynamic body */

    // Box2D
    float dynBodyPosX = 35.0f;
    float dynBodyPosY = 40.0f;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(dynBodyPosX, dynBodyPosY);
    b2Body * body = testSimWorld.getWorld()->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetTransform(b2Vec2(dynBodyPosX,dynBodyPosX), M_PI/3);


    // QGraphics
    QGraphicsRectItem box;


    // First two parameters are setting the local origin point in the middle of the rectangle
    // so that it complies with Box2D coordinates. May be harder to implement with general polygons.
    box.setRect(-10,-10, 20, 20);
    testSimWorld.getScene()->addItem(&box);
    cout << "First position: " <<  dynBodyPosX*scaleFactor << " " << sceneHeight - dynBodyPosY*scaleFactor << endl;

    /* END_OF: Create dynamic body */


    testView.setFixedSize(sceneWidth,sceneHeight);
    testView.show();

    testSimWorld.addObject(make_pair(&groundRectangle, groundBody));

    testSimWorld.addObject(make_pair(&box, body));


    // Simulating the world

    testSimWorld.startSimulation();

    return a.exec();
}
