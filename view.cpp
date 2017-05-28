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
          for(int i = 0; i < count; ++i)
          {
             verts.push_back(_model->chromosomeCarBodyPtr->GetWorldPoint( poly->GetVertex(i) ));
          }

          //verts now contains world co-ords of all the verts
       }
    }

    QVector<QPoint> qPoints;
    for(uint i = 0; i < verts.size(); ++i){
        qPoints.push_back(QPoint( (verts[i].x + 400), (300 - verts[i].y) ));
        ++i;
    }

    QPolygon car = QPolygon(qPoints);

   p.drawPolygon(car);

    _drawer->setPainter(&p);
    _model->DrawModelData();

    p.end();
}
