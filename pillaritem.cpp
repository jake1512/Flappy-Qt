#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>

PillarItem::PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/pipe_up.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/pipe_down.png")))
{
    bottomPillar->setPos(QPointF(0,0) - QPointF(bottomPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 60));
    topPillar->setPos(QPointF(0,0) + QPointF(-topPillar->boundingRect().width()/2, 60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

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
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal x)
{
    qDebug() << "Pillar position : " << x;
    m_x = x;
    setPos(QPointF(0,0) + QPointF(x,yPos));
}
