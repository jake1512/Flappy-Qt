#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QDebug>
#include "mainwindow.h"
#include "ground.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),
    score(0),
    bestScore(0)
{
    setUpPillarTime();

}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/new/prefix1/images/bird_blue_up.png"));
    addItem(bird);
}

void Scene::startGame()
{
    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive()){
        cleanPillars();
        setGameOn(true);
        hideGameOverGraphics();
        score = 0;
        pillarTimer->start(2000);
        //        groundTimer->start(1000);
    }
}

void Scene::setUpPillarTime()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){

        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem, &PillarItem::collideFail, [=](){
            pillarTimer->stop();
            freeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });

        addItem(pillarItem);
    });

    //    pillarTimer->start(1000);

}


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


bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
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

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }         
    }
    if(event->button() == Qt::RightButton){
        if(gameOn){
            delete scorePresentPlay;
        }
    }
    QGraphicsScene::mousePressEvent(event);

}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/gameOver.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0, 0) - QPointF(gameOverPix->boundingRect().width()/2,
                                                gameOverPix->boundingRect().height()));
    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = "<p> Score      : " + QString::number(score) + " </p"
            +"<p> Best Score : " + QString::number(bestScore) + " </p>";

    QFont mFont("Consolas", 25, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0, 0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                  - gameOverPix->boundingRect().height()/2));

}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix){
            // removeItem(gameOverPix);
            delete gameOverPix;
            gameOverPix = nullptr;
    }
    if(scoreTextItem){
//        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
    if(scorePresentPlay){
//        removeItem(scorePresentPlay);
        delete scorePresentPlay;
        scorePresentPlay = nullptr;
    }
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
