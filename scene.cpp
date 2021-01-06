#include "scene.h"
#include "common.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QPainter>
#include "mainwindow.h"
#include "ground.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    score = 0;
    bestScore = 0;

    gameFinished = 0;
    gameStarted = 0;
    gameActuallyStarted = 0;

    setUpPillarTime();

    QPixmap pixmap_scoreBoard(IMG_SCOREBOARD);
    item_pixmap_scoreBoard = new QGraphicsPixmapItem(pixmap_scoreBoard);
    item_pixmap_scoreBoard->setPos(QPointF(0, 0) - QPointF(item_pixmap_scoreBoard->boundingRect().width()/2,
                                                    item_pixmap_scoreBoard->boundingRect().height()));
    item_pixmap_scoreBoard->setVisible(false);

    addItem(item_pixmap_scoreBoard);
}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(IMG_BIRD_BLUE_UP));
    addItem(bird);
}

void Scene::startGame()
{
    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive()){
        cleanPillars();
        gameFinished = false;
        gameActuallyStarted = true;
        pillarTimer->start(1000);
    }
}

void Scene::prepareNewRound()
{
    delete bird;

}

void Scene::setUpPillarTime()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){

        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem, &PillarItem::collideFail, [=](){
            pillarTimer->stop();
            freeBirdAndPillarsInPlace();
            gameFinished = true;
            gameActuallyStarted = false;
            gameOver(score);
        });

        addItem(pillarItem);
    });

    //    pillarTimer->start(1000);

}

// bird crashes into pillar
void Scene::freeBirdAndPillarsInPlace()
{
    bird->freezeInPlace();

    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems){
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
            pillar->freezeInPlace();
        }
    }
}


bool Scene::isGameFinished()
{
    return gameFinished;
}

bool Scene::isGameStarted()
{
    return gameStarted;
}

bool Scene::isGameActuallyStarted()
{
    return gameActuallyStarted;
}

void Scene::incrementScore()
{
    score++;
    delete scorePresentPlay;
    updateScore();
    if(score > bestScore)
        bestScore = score;

}

void Scene::updateScore()
{
    scorePresentPlay = new QGraphicsTextItem();

    QFont mFont1("Consolas", 55, QFont::Bold);

    QString  htmlString1 =  QString::number(score);

    scorePresentPlay->setHtml(htmlString1);
    scorePresentPlay->setFont(mFont1);
    scorePresentPlay->setDefaultTextColor(Qt::yellow);
    scorePresentPlay->setPos(QPointF(0, 0) - QPointF(scorePresentPlay->boundingRect().width()/2,
                                                     250));
    addItem(scorePresentPlay);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameActuallyStarted){
            bird->shootUp();
        }         
    }
    QGraphicsScene::mousePressEvent(event);

}

void Scene::gameOver(int score)
{
    QPixmap reward = QPixmap(IMG_SCOREBOARD);
        if(score >= 10 && score < 20)
            reward = QPixmap(IMG_SCOREBOARD_BRONZE);
        else if(score >= 20 && score < 30)
            reward = QPixmap(IMG_SCOREBOARD_SILVER);
        else if(score >= 30 && score < 40)
            reward = QPixmap(IMG_SCOREBOARD_GOLD);
        else if(score >= 40)
            reward = QPixmap(IMG_SCOREBOARD_PLATINUM);

        item_pixmap_scoreBoard->setPixmap(reward);

        gameFinished = true;
        gameActuallyStarted = false;
}
void Scene::cleanPillars()
{
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }
    }
}
