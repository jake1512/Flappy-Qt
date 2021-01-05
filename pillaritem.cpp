#include "pillaritem.h"
#include "common.h"
#include <QRandomGenerator>
#include <QDebug>
#include "scene.h"
#include "birditem.h"
#include "mainwindow.h"
#include <QGraphicsScene>

PillarItem::PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(IMG_PIPE_UP))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(IMG_PIPE_DOWN))),
    pastBird(false)
{
    bottomPillar->setPos(QPointF(0,0) - QPointF(bottomPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 60));
    topPillar->setPos(QPointF(0, 0) + QPointF(-topPillar->boundingRect().width()/2, 60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);


    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(650 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(650 + xRandomizer);
    xAnimation->setEndValue(-650);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(3750);

    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();

    addToGroup(topPillar);
    addToGroup(bottomPillar);

}

PillarItem::~PillarItem()
{
    qDebug() << "Deleting Pillar";
    delete  topPillar;
    delete  bottomPillar;

}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x)
{
    //    qDebug() << "Pillar position : " << x;
    m_x = x;

    if(x < 0 && !pastBird){
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene * >(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }

    if(collideWithBird()){
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));
}



bool PillarItem::collideWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem * item, collidingItems){
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}
