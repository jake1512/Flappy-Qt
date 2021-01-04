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
    bool getGameOn() const;
    void setGameOn(bool value);
    void updateScore();
    void incrementScore();



signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTime();
    void freeBirdAndPillarsInPlace();


    QTimer * pillarTimer;
    QTimer * groundTimer;
    BirdItem * bird;
    bool gameOn;

    int score, scoreBefore;
    int bestScore;

    QGraphicsItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsTextItem * scorePresentPlay;



};

#endif // SCENE_H
