#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class PillarItem :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem();

    qreal x() const;

    void freezeInPlace();

public slots:
    void setX(qreal x);

signals:
    void collideFail();

private:

    bool collidesWithBird();

    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation * xAnimation;
//    QGraphicsPixmapItem * ground;
    int yPos;

    qreal m_x;
    bool pastBird;
};

#endif // PILLARITEM_H
