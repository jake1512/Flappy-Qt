#include "pillaritem.h"
#include "common.h"
#include <QRandomGenerator>
#include <birditem.h>
#include <QDebug>
#include <QGraphicsScene>
#include <scene.h>

PillarItem::PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(IMG_PIPE_UP))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(IMG_PIPE_DOWN))),
//    ground(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/ground_segment.png"))),
    pastBird(false)
{
    bottomPillar->setPos(QPointF(0,0) - QPointF(bottomPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 40));
    topPillar->setPos(QPointF(0,30) + QPointF(-topPillar->boundingRect().width()/2, 40));
//    ground->setPos(QPointF(0, 0) -QPointF(ground->boundingRect().width()/2, -290));

    addToGroup(topPillar);
    addToGroup(bottomPillar);
//    addToGroup(ground);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(700 + xRandomizer);
    xAnimation->setEndValue(-700);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(4000);

    connect(xAnimation, &QPropertyAnimation::finished,[=](){
//        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();

    addToGroup(topPillar);
    addToGroup(bottomPillar);
//    addToGroup(ground);

}

PillarItem::~PillarItem()
{
//    qDebug() << "Deleting Pillar";
    delete topPillar;
    delete bottomPillar;
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

    if(x < 0 && !pastBird)
    {
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if(myScene)
        {
            myScene->incrementScore();

        }

    }

    if(collidesWithBird())
    {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));
}

bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItem = topPillar->collidingItems();
    collidingItem.append(bottomPillar->collidingItems());

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
