#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include "pillaritem.h"
#include "scene.h"
#include "birditem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-144, -256, 288, 512);

    pixItem = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/background_day.png"));
    logo = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/logo.png"));
    tap = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/gameInfo.png"));
    ground = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/ground_segment.png"));

    scene->addItem(pixItem);
    scene->addItem(logo);
    scene->addItem(tap);
    scene->addItem(ground);

    pixItem->setPos(QPointF(0, 0) -QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));
    logo->setPos(QPointF(0, 0) -QPointF(logo->boundingRect().width()/2, pixItem->boundingRect().height()/8));
    tap->setPos(QPointF(0, 0) -QPointF(tap->boundingRect().width()/2, -pixItem->boundingRect().height()/20));

    ground->setPos(QPointF(0, 0) -QPointF(ground->boundingRect().width()/2, -pixItem->boundingRect().height()/4));


//    scene->addLine(-400, 0, 400, 0, QPen(Qt::blue));
//    scene->addLine(0, -400, 0, 400, QPen(Qt::blue));
//    QGraphicsScene * mScene = scene;
    //    Scene * myScene = dynamic_cast<Scene * >(mScene);
    //    if(myScene){
    //        myScene->updateScore();
    //    }

    ui->graphicsView->setScene(scene);

    scene->addBird();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_startGame_clicked()
{
    scene->startGame();
    if (logo->isActive()) {
        delete logo;
    }
    if (tap->isActive()){
        delete tap;
    }

}
