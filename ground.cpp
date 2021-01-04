#include "ground.h"
#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include "scene.h"
#include "birditem.h"
#include <QGraphicsScene>

ground::ground() :
    groundback(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/ground_segment.png")))
{
    groundback->setPos(QPointF(0, 0));

    gAnimation = new QPropertyAnimation(this, "g", this);
    gAnimation->setStartValue(650);
    gAnimation->setEndValue(-650);
    gAnimation->setEasingCurve(QEasingCurve::Linear);
    gAnimation->setDuration(1000);

    connect(gAnimation, &QPropertyAnimation::finished,[=](){
        scene()->removeItem(this);
        delete this;
    });

    gAnimation->start();


    scene()->addItem(groundback);}

ground::~ground()
{
    delete groundback;
}

qreal ground::x() const
{
    return m_x;
}


void ground::setX(qreal x)
{
//    qDebug() << "Pillar position : " << x;
    m_x = x;

//    if(x < 0 && !pastBird){
//        pastBird = true;
//        QGraphicsScene * mScene = scene();
//        Scene * myScene = dynamic_cast<Scene * >(mScene);
//        if(myScene){
//            myScene->incrementScore();
//        }

//    }

//    if(collideWithBird()){
//        emit collideFail();
//    }
//    setPos(QPointF(0,0) + QPointF(x,yPos));
}

//bool PillarItem::collideWithBird()
//{
//    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
//    collidingItems.append(bottomPillar->collidingItems());

//    foreach(QGraphicsItem * item, collidingItems){
//        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
//        if(birdItem){
//            return true;
//        }
//    }
//    return false;
//}
