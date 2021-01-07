#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include "common.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),
    score(0),
    bestScore(0)
{
    setUpPillarTime();
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
    if(!pillarTimer->isActive())
    {
        cleanPillars();
        setGameOn(true);
        setScore(0);
        hideGameOvergraphics();
        pillarTimer->start(1000);
    }
}

void Scene::setUpPillarTime()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){

        PillarItem * pillarItem = new PillarItem();

        connect(pillarItem, &PillarItem::collideFail,[=](){
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });

        addItem(pillarItem);
    });

//    pillarTimer->start(1000);

}

void Scene::freezeBirdAndPillarsInPlace()
{
    //freeze Bird
    bird->freezeInPlace();

    //freeze plillars
    QList<QGraphicsItem *> sceneItem = items();
    foreach(QGraphicsItem *item, sceneItem)
    {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar)
        {
            pillar->freezeInPlace();
        }
    }
}

void Scene::setScore(int value)
{
    score = value;
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
    delete  scorePresentPlay;
    updateScore();
    if(score > bestScore)
    {
        bestScore = score;
    }
    qDebug() << "Score : " << score << "best Score : " << bestScore;
}

void Scene::updateScore()
{
    scorePresentPlay = new QGraphicsTextItem();

    QFont mFont1("Consolas", 55, QFont::Bold);

    QString  htmlString1 =  QString::number(score);

    scorePresentPlay->setHtml(htmlString1);
    scorePresentPlay->setFont(mFont1);
    scorePresentPlay->setDefaultTextColor(Qt::red);
    scorePresentPlay->setPos(QPointF(0, 0) - QPointF(scorePresentPlay->boundingRect().width()/2,
                                                     250));
    addItem(scorePresentPlay);
}
void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        if(gameOn)
        {
            bird->shootUP();
        }

    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(gameOn)
        {
            bird->shootUP();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressEvent(event);
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(IMG_GAMEOVER));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));
    scoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> Score : " + QString::number(score) + "</p>"
            + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    QFont mFont("Calibri", 30, QFont::Normal);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::blue);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOvergraphics()
{
    if(gameOverPix)
    {
//        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem)
    {
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
    QList<QGraphicsItem *> sceneItem = items();
    foreach(QGraphicsItem *item, sceneItem)
    {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar)
        {
            removeItem(pillar);
            delete pillar;
        }
    }
}
