#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTime();

}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/new/prefix1/images/bird_blue_up.png"));
    addItem(bird);
}

void Scene::setUpPillarTime()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){

        PillarItem * pillarItem = new PillarItem();

        addItem(pillarItem);


    });

    pillarTimer->start(1000);

}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 if(event->button() == Qt::LeftButton){
     bird->shootUp();
 }
 QGraphicsScene::mousePressEvent(event);
}
