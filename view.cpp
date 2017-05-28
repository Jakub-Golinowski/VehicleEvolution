#include "view.h"
#include <vector>
#include <sstream>

const float32 View::DRAWING_SCALE = 2;

View::View(Model * model, QB2Draw * drawer)
    :_model(model), _drawer(drawer)
{

}

void View::paintEvent(QPaintEvent *event)
{
    //Set up the painter parameters

    QPainter p(this);
    p.setBrush(Qt::NoBrush);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);
    QTransform transform;

    //Retrieve car position and angle
    b2Vec2 CarPosition = _model->chromosomeCarBodyPtr->GetPosition();
    transform.scale(DRAWING_SCALE,DRAWING_SCALE);
    transform.translate(-(CarPosition.x), CarPosition.y);

    p.setTransform(transform);

    //Retrieve all vertices of car body triangles and draw the car body triangles in scale
    for( b2Fixture *fixture = _model->chromosomeCarBodyPtr->GetFixtureList(); fixture; fixture = fixture->GetNext() )
    {
       if( fixture->GetShape()->GetType() == b2Shape::e_polygon )
       {
          b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();
          QVector<QPoint> singleTriangle;

          int count = poly->GetVertexCount();
          for(int i = 0; i < count; ++i)
          {
             b2Vec2 Vertex = _model->chromosomeCarBodyPtr->GetWorldPoint( poly->GetVertex(i) );
             singleTriangle.append(QPoint((Vertex.x + 400/DRAWING_SCALE),(300/DRAWING_SCALE - Vertex.y)));
             p.drawPolygon(singleTriangle, Qt::WindingFill);
          }
       }
    }

    //Retrieve car wheels and draw them to scale
    for( b2Body* wheel : _model->WheelBodyPtrArray)
    {
        QPointF wheelCenter = QPoint(wheel->GetPosition().x + 400/DRAWING_SCALE, 300/DRAWING_SCALE - wheel->GetPosition().y);
        qreal wheelRadius = 0;

        for (b2Fixture* f = wheel->GetFixtureList(); f; f = f->GetNext())
        {
            b2Shape::Type shapeType = f->GetType();
            if ( shapeType == b2Shape::e_circle )
            {
                b2CircleShape* circleShape = (b2CircleShape*)f->GetShape();
                wheelRadius = circleShape->m_radius;
            }
        }

        float32 angleRadians = -wheel->GetAngle();

        float32 xLength = cos(angleRadians) * wheelRadius;
        float32 yLength = sin(angleRadians) * wheelRadius;

        QPointF wheelCircumferencePoint = QPointF(wheelCenter.x() + xLength, wheelCenter.y() + yLength);
        p.drawLine(wheelCenter, wheelCircumferencePoint);

        p.drawEllipse(wheelCenter,wheelRadius,wheelRadius);
    }

    std::stringstream s;
    s << "Przejechany dystans: " << CarPosition.x;
    std::string distanceMessage = s.str();

    p.drawText(CarPosition.x+ 400/(DRAWING_SCALE*2) , 300/(DRAWING_SCALE*2) -CarPosition.y, QString::fromStdString(distanceMessage) );

    _drawer->setPainter(&p);
    _model->DrawModelData();

    p.end();
}
