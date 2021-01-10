#include "scene.h"
#include "common.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include <QGraphicsDropShadowEffect>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),
    score(0),
    bestScore(0)
{
    setUpPillarTime();
    setUpGround();
}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(IMG_BIRD_BLUE_UP));
    addItem(bird);
}

void Scene::groundRun()
{

}

void Scene::startGame()
{

    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive())
    {
        cleanPillars();
        //        cleanGround();
        setGameOn(true);
        setScore(0);
        hideGameOvergraphics();
        pillarTimer->start(1000);
        groundTimer->start(200);
    }

}

void Scene::setUpPillarTime()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){

        PillarItem * pillarItem = new PillarItem();

        connect(pillarItem, &PillarItem::collideFail,[=](){
            pillarTimer->stop();
            groundTimer->stop();
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
    QMediaPlayer * falldown = new QMediaPlayer();
    falldown->setMedia(QUrl(SND_HIT));
    //freeze plillars
    QList<QGraphicsItem *> sceneItem = items();
    foreach(QGraphicsItem *item, sceneItem)
    {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar)
        {
            pillar->freezeInPlace();
            falldown->play();
        }
    }

    QList<QGraphicsItem *> sceneItemG = items();
    foreach(QGraphicsItem *item, sceneItemG)
    {
        GroundItem * ground = dynamic_cast<GroundItem *>(item);
        if(ground)
        {
            ground->freezeInPlaceG();
            falldown->play();
        }
    }
}

void Scene::setUpGround()
{
    groundTimer = new QTimer(this);
    connect(groundTimer,&QTimer::timeout,[=](){

        GroundItem * grounditem = new GroundItem();

        connect(grounditem, &GroundItem::collideFailG,[=](){
            pillarTimer->stop();
            groundTimer->stop();
            freezeBirdAndPillarsInPlace();
            hideGameOvergraphics();
            setGameOn(false);
            showGameOverGraphics();
        });

        addItem(grounditem);
    });

    groundTimer->start(200);
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
    QMediaPlayer * scoreAdd = new QMediaPlayer();
    scoreAdd->setMedia(QUrl(SND_POINT));
    scoreAdd->play();
    delete  scorePresentPlay;
    updateScore();
    if(score > bestScore)
    {
        bestScore = score;
    }
//    qDebug() << "Score : " << score << "best Score : " << bestScore;
}

void Scene::updateScore()
{
    effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(0);
    effect->setColor(QColor("#000000"));
    effect->setOffset(4,4);

    scorePresentPlay = new QGraphicsTextItem();

    QFont mFont1("Calibri Light", 60, QFont::Bold);

    QString  htmlString1 =  QString::number(score);

    scorePresentPlay->setGraphicsEffect(effect);
    scorePresentPlay->setHtml(htmlString1);
    scorePresentPlay->setFont(mFont1);
    scorePresentPlay->setDefaultTextColor(Qt::white);
    scorePresentPlay->setPos(QPointF(0, 0) - QPointF(scorePresentPlay->boundingRect().width()/2, 250));
    addItem(scorePresentPlay);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        if(gameOn)
        {
            bird->shootUP();
            QMediaPlayer * wing = new QMediaPlayer();
            wing->setMedia(QUrl(SND_WING));
            wing->play();
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
            QMediaPlayer * wing = new QMediaPlayer();
            wing->setMedia(QUrl(SND_WING));
            wing->play();
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
    if(score >= 0 && score < 10)
    {
        gameOverScore = new QGraphicsPixmapItem(QPixmap(IMG_SCOREBOARD));
    }else if( score >= 10 && score < 20)
    {
        gameOverScore = new QGraphicsPixmapItem(QPixmap(IMG_SCOREBOARD_BRONZE));
    } else if( score >= 20 && score < 30)
    {
        gameOverScore = new QGraphicsPixmapItem(QPixmap(IMG_SCOREBOARD_SILVER));
    }  else if( score >= 30 && score < 40)
    {
        gameOverScore = new QGraphicsPixmapItem(QPixmap(IMG_SCOREBOARD_GOLD));
    } else if( score >= 50)
    {
        gameOverScore = new QGraphicsPixmapItem(QPixmap(IMG_SCOREBOARD_PLATINUM));
    }
    gameOverPix = new QGraphicsPixmapItem(QPixmap(IMG_GAMEOVER));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));

    addItem(gameOverScore);
    gameOverScore->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2 + 15,
                                                 -50));

    scoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> " + QString::number(score) + "</p>"
            + "<p>" + QString::number(bestScore) + "</p>";

    QFont mFont("Calibri Light", 17, QFont::Bold);

    effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(0);
    effect->setColor(QColor("#000000"));
    effect->setOffset(1,1);

    scoreTextItem->setGraphicsEffect(effect);
    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::white);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2 -70,
                                                 -gameOverPix->boundingRect().height()/2 - 47));
}

void Scene::hideGameOvergraphics()
{
    if(gameOverPix)
    {
        // removeItem(gameOverPix);
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
    if(gameOverScore){
        //        removeItem(scorePresentPlay);
        delete gameOverScore;
        gameOverScore = nullptr;
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

void Scene::cleanGround()
{
    QList<QGraphicsItem *> sceneItemG = items();
    foreach(QGraphicsItem *item, sceneItemG)
    {
        GroundItem * ground = dynamic_cast<GroundItem *>(item);
        if(ground)
        {
            removeItem(ground);
            delete ground;
        }
    }
}
