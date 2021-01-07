#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include <birditem.h>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

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
    void setUpPillarTime();
    void freezeBirdAndPillarsInPlace();

    QTimer * pillarTimer;

    BirdItem * bird;

    bool gameOn;

    int score;
    int bestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsTextItem * scorePresentPlay;

};



#endif // SCENE_H
