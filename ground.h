#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class ground :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit ground();
    ~ground();

    qreal x() const;

//    void freezeInPlace();

public slots:
    void setX(qreal x);

signals:
//    void collideFail();

private:

//    bool collideWithBird();

    QGraphicsPixmapItem * groundback;
    QPropertyAnimation * gAnimation;
    int yPos;

    qreal m_x;
//    bool pastBird;
};

#endif // GROUND_H
