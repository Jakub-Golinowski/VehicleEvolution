#include "view.h"
#include <vector>




View::View(Model * model, QB2Draw * drawer)
    :_model(model), _drawer(drawer)
{

}

void View::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    b2Vec2 CarPosition = _model->chromosomeCarBodyPtr->GetPosition();
    float angle = _model->chromosomeCarBodyPtr->GetAngle();

    //draw a polygon
std::vector<b2Vec2> verts;
    for( b2Fixture *fixture = _model->chromosomeCarBodyPtr->GetFixtureList(); fixture; fixture = fixture->GetNext() )
    {
       if( fixture->GetShape()->GetType() == b2Shape::e_polygon )
       {
          b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();



          int count = poly->GetVertexCount();
          for(int i = 0; i < poly->GetVertexCount(); ++i)
          {
             verts.push_back(poly->GetVertex(i));
          }

          for( int i = 0; i < count; i++ )
          {
             verts[i] = _model->chromosomeCarBodyPtr->GetWorldPoint( verts[i] );
          }

          //verts now contains world co-ords of all the verts
       }
    }
    int *points = new int[verts.size()*2];
    for(int i = 0; i < 2*verts.size(); ++i){
        points[i] = verts[i].x;
        points[i+ 1] = verts[i].y;
        ++i;
    }

    QPolygon car = QPolygon(static_cast<int>(verts.size()), points );

    int halfwidth = 100;
    qreal mfltElevation = 10.0;
    QPolygon plyNeedle;
       plyNeedle << QPoint(CarPosition.x - halfwidth + 400, CarPosition.y - halfwidth + 300)
                 << QPoint(CarPosition.x - halfwidth + 400, CarPosition.y + halfwidth + 300)
                 << QPoint(CarPosition.x + halfwidth + 400, CarPosition.y - halfwidth + 300)
                 << QPoint(CarPosition.x + halfwidth + 400, CarPosition.y + halfwidth + 300);

   plyNeedle = QTransform().translate(CarPosition.x, CarPosition.y)
                               .rotate(-mfltElevation)
                               .translate(-CarPosition.x, -CarPosition.y)
                               .map(plyNeedle);
    p.drawPolygon(car);


    //CarPosition.x-400, -(CarPosition.y+300)




    _drawer->setPainter(&p);
    _model->DrawModelData();

    p.end();
}
