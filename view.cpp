#include "view.h"
#include <vector>
#include <sstream>

const float32 View::DRAWING_SCALE = 6;

View::View(Model * model):_model(model)
{

}

View::View()
{
    _model=nullptr;
}

void View::paintEvent(QPaintEvent *event)
{
    //Set up the painter parameters
    QPainter p(this);
    p.setBrush(Qt::NoBrush);
    QPen pen;
    pen.setWidth(1);
    p.setPen(pen);
    QTransform transform;

    //Retrieve car position and angle
    b2Vec2 CarPosition = _model->chromosomeCarBodyPtr->GetPosition();
    // Translation moves point (0;0) to the middle of the view
    transform.translate(this->geometry().width()/2,this->geometry().height()/2);
    transform.scale(DRAWING_SCALE,-DRAWING_SCALE);
    transform.translate(-(qreal(CarPosition.x)), -qreal(CarPosition.y));
    p.setTransform(transform);


    //Retrieve all vertices of car body triangles and draw the car body triangles in scale
    for( b2Fixture *fixture = _model->chromosomeCarBodyPtr->GetFixtureList(); fixture; fixture = fixture->GetNext() )
    {
       if( fixture->GetShape()->GetType() == b2Shape::e_polygon )
       {
          b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();
          QVector<QPointF> singleTriangle;

          int count = poly->GetVertexCount();
          for(int i = 0; i < count; ++i)
          {
             b2Vec2 Vertex = _model->chromosomeCarBodyPtr->GetWorldPoint( poly->GetVertex(i) );
             singleTriangle.append(QPointF((Vertex.x),(Vertex.y)));
             p.drawPolygon(singleTriangle);
          }
       }
    }

    //Retrieve car wheels and draw them to scale
    for( b2Body* wheel : _model->WheelBodyPtrArray)
    {
        QPointF wheelCenter = QPointF(wheel->GetPosition().x , wheel->GetPosition().y);
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

        float32 angleRadians = wheel->GetAngle();

        float32 xLength = cos(angleRadians) * wheelRadius;
        float32 yLength = sin(angleRadians) * wheelRadius;

        QPointF wheelCircumferencePoint = QPointF(wheelCenter.x() + xLength, wheelCenter.y() + yLength);
        p.drawLine(wheelCenter, wheelCircumferencePoint);

        p.drawEllipse(wheelCenter,wheelRadius,wheelRadius);
    }

    //Draw ground chain shape
    b2Fixture *fixture = _model->groundBodyPtr->GetFixtureList();
    if( fixture->GetShape()->GetType() == b2Shape::e_chain )
    {
      b2ChainShape *chain = (b2ChainShape*)fixture->GetShape();
      float groundBodyXOffset = _model->groundBodyPtr->GetPosition().x;
      float groundBodyYOffset = _model->groundBodyPtr->GetPosition().y;

      for(int i = 0; i < chain->GetChildCount(); ++i)
      {
         b2EdgeShape edge;
         chain->GetChildEdge(&edge, i);
         p.drawLine(QPointF(groundBodyXOffset + edge.m_vertex1.x,edge.m_vertex1.y+groundBodyYOffset), QPointF(groundBodyXOffset + edge.m_vertex2.x,edge.m_vertex2.y+groundBodyYOffset));
      }
    }


    std::stringstream s;
    s << "Przejechany dystans: " << CarPosition.x;
    std::string distanceMessage = s.str();


    QFont font;
    font.setPixelSize(18/DRAWING_SCALE);
    // Change scaling in Y axis, so the text won't be upside down
    transform.scale(1,-1);
    p.setFont(font);
    p.setTransform(transform);
    p.drawText(QPointF((CarPosition.x-this->geometry().height()/(3*DRAWING_SCALE)), -(CarPosition.y - this->geometry().height()/(3*DRAWING_SCALE))), QString::fromStdString(distanceMessage) );

    p.end();
}


QSize View::sizeHint() const
{
    return QSize(800, 600);
}

QSize View::minimumSizeHint() const
{
    return QSize(800, 600);
}

