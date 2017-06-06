/*!
 * @file View.cpp
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief View class implementation
 */

#include "view.h"
#include <vector>
#include <QPen>
#include <QPainter>
#include <QTransform>
#include <sstream>

const float32 View::DRAWING_SCALE = 6.0;
const int View::PEN_WIDTH = 1;
const float32 View::ORIGINAL_PIXEL_SIZE = 18.0;
const float View::DISTANCE_STRING_PROPER_PLACEMENT_COEFFICIENT = 3.0;


View::View(Model * model):model_(model)
{

}

void View::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //Set up the painter parameters
    QPainter p(this);
    p.setBrush(Qt::NoBrush);
    QPen pen;
    pen.setWidth(PEN_WIDTH);
    p.setPen(pen);
    QTransform transform;

    if( !model_->chromosomeCarBodyPtr_ )
    {
        p.drawText(this->geometry(), Qt::AlignCenter, "Brak chromosomów, wygeneruj pierwszą populację.");
        p.end();
        return;
    }
    //Retrieve car position and angle
    b2Vec2 CarPosition = model_->chromosomeCarBodyPtr_->GetPosition();
    // Translation moves point (0;0) to the middle of the view
    transform.translate(this->geometry().width()/2,this->geometry().height()/2);
    transform.scale(DRAWING_SCALE,-DRAWING_SCALE);
    transform.translate(-(qreal(CarPosition.x)), -qreal(CarPosition.y));
    p.setTransform(transform);


    //Retrieve all vertices of car body triangles and draw the car body triangles in scale
    for( b2Fixture *fixture = model_->chromosomeCarBodyPtr_->GetFixtureList(); fixture; fixture = fixture->GetNext() )
    {
       if( fixture->GetShape()->GetType() == b2Shape::e_polygon )
       {
          b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();
          QVector<QPointF> singleTriangle;

          int count = poly->GetVertexCount();
          for(int i = 0; i < count; ++i)
          {
             b2Vec2 Vertex = model_->chromosomeCarBodyPtr_->GetWorldPoint( poly->GetVertex(i) );
             singleTriangle.append(QPointF((Vertex.x),(Vertex.y)));
             p.drawPolygon(singleTriangle);
          }
       }
    }

    //Retrieve car wheels and draw them to scale
    for( b2Body* wheel : model_->WheelBodyPtrArray)
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
    b2Fixture *fixture = model_->groundBodyPtr_->GetFixtureList();
    if( fixture->GetShape()->GetType() == b2Shape::e_chain )
    {
      b2ChainShape *chain = (b2ChainShape*)fixture->GetShape();
      float groundBodyXOffset = model_->groundBodyPtr_->GetPosition().x;
      float groundBodyYOffset = model_->groundBodyPtr_->GetPosition().y;

      for(int i = 0; i < chain->GetChildCount(); ++i)
      {
         b2EdgeShape edge;
         chain->GetChildEdge(&edge, i);
         p.drawLine(QPointF(groundBodyXOffset + edge.m_vertex1.x,edge.m_vertex1.y+groundBodyYOffset), QPointF(groundBodyXOffset + edge.m_vertex2.x,edge.m_vertex2.y+groundBodyYOffset));
      }
    }

    //Draw distance info
    std::stringstream s;
    s << "Przejechany dystans: " << CarPosition.x;
    std::string distanceMessage = s.str();
    QFont font;
    font.setPixelSize(ORIGINAL_PIXEL_SIZE/DRAWING_SCALE);
    // Change scaling in Y axis, so the text won't be upside down
    transform.scale(1,-1);
    p.setFont(font);
    p.setTransform(transform);
    p.drawText(QPointF((CarPosition.x-this->geometry().height()/(DISTANCE_STRING_PROPER_PLACEMENT_COEFFICIENT*DRAWING_SCALE)), -(CarPosition.y - this->geometry().height()/(DISTANCE_STRING_PROPER_PLACEMENT_COEFFICIENT*DRAWING_SCALE))), QString::fromStdString(distanceMessage) );

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

