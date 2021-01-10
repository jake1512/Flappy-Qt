#ifndef GROUNDITEM_H
#define GROUNDITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class GroundItem :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit GroundItem();
    ~GroundItem();

    qreal x() const;

    void freezeInPlaceG();
public slots:
    void setX(qreal x);

signals:
    void collideFailG();

private:
    bool collidesWithBirdG();
    QGraphicsPixmapItem * grounditem;
    QPropertyAnimation * xAnimation;

    int yPos;

    qreal m_x;
    bool pastBird;
};

#endif // GROUNDITEM_H
