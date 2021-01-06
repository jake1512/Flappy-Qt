#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

    void startGame();

    void updateScore();
    void incrementScore();

    void gameOver(int score);

    bool isGameStarted();
    bool isGameFinished();
    bool isGameActuallyStarted();

    void prepareNewRound();

signals:

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void cleanPillars();
    void setUpPillarTime();
    void freeBirdAndPillarsInPlace();

    bool gameFinished, gameStarted;
    bool gameActuallyStarted;

    QTimer * pillarTimer;
    QTimer * groundTimer;
    BirdItem * bird;

    int score, scoreBefore;
    int bestScore;


    QGraphicsTextItem * scoreTextItem;
    QGraphicsTextItem * scorePresentPlay;

    QGraphicsPixmapItem *item_pixmap_scoreBoard;

};

#endif // SCENE_H
