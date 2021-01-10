#include "grounditem.h"
#include "common.h"
#include <birditem.h>
#include <QDebug>
#include <QGraphicsScene>
#include <scene.h>

GroundItem::GroundItem() :
    grounditem(new QGraphicsPixmapItem(QPixmap(IMG_GROUND_SEGMENT)))
{
    grounditem->setPos(QPointF(0,0) - QPointF(grounditem->boundingRect().width()/2, -290));

    addToGroup(grounditem);
    setPos(QPoint(0,0) + QPoint(260 , yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(300);
    xAnimation->setEndValue(-700);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(3000);

    connect(xAnimation, &QPropertyAnimation::finished,[=](){
//        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();

    addToGroup(grounditem);


}

GroundItem::~GroundItem()
{
//    qDebug() << "Deleting ground";
    delete grounditem;
}

qreal GroundItem::x() const
{
    return m_x;
}
void GroundItem::freezeInPlaceG()
{
    xAnimation->stop();
}
void GroundItem::setX(qreal x)
{
//    qDebug() << "Pillar position : " << x;
    m_x = x;
    if(collidesWithBirdG())
    {
        emit collideFailG();
    }

    setPos(QPointF(0,0) + QPointF(x,yPos));
}
bool GroundItem::collidesWithBirdG()
{
    QList<QGraphicsItem*> collidingItem = grounditem->collidingItems();

    foreach(QGraphicsItem * item, collidingItem)
    {
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem)
        {
            return true;
        }
    }
    return false;
}

