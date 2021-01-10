#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>


class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit BirdItem(QPixmap pixmap);

    qreal rotation() const;

    qreal y() const;

    void shootUP();

    void startFlying();

    void freezeInPlace();

public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);

    void fallToGroundIfNecessary();

signals:
private:
    enum WingPositon{
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    WingPositon wingPositon;
    bool wingDirection; // 0 : down, 1 : up

    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    qreal groundPosition;
};

#endif // BIRDITEM_H
