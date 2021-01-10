#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include <grounditem.h>
#include <birditem.h>
#include <QGraphicsDropShadowEffect>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();
    void groundRun();
    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);
    void updateScore();
    void incrementScore();

    void setScore(int value);

signals:
public slots:

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void hideGameOvergraphics();
    void cleanPillars();
    void cleanGround();
    void setUpPillarTime();
    void freezeBirdAndPillarsInPlace();
    void setUpGround();

    QTimer * pillarTimer;
    QTimer * groundTimer;

    BirdItem * bird;

    bool gameOn;

    int score;
    int bestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsPixmapItem * gameOverScore;
    QGraphicsTextItem * scoreTextItem;

    QGraphicsTextItem * scorePresentPlay;
    QGraphicsDropShadowEffect *effect;

};



#endif // SCENE_H
