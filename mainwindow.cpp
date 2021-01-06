#include "mainwindow.h"
#include "common.h"
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

    background = new QGraphicsPixmapItem(QPixmap(IMG_BACKGROUND_DAY));
    logo = new QGraphicsPixmapItem(QPixmap(IMG_LOGO));
    tap = new QGraphicsPixmapItem(QPixmap(IMG_GAMEINFO));
    ground = new QGraphicsPixmapItem(QPixmap(IMG_GROUND_SEGMENT));

    scene->addItem(background);
    scene->addItem(logo);
    scene->addItem(tap);
    scene->addItem(ground);

    background->setPos(QPointF(0, 0) -QPointF(background->boundingRect().width()/2, background->boundingRect().height()/2));
    logo->setPos(QPointF(0, 0) -QPointF(logo->boundingRect().width()/2, background->boundingRect().height()/8));
    tap->setPos(QPointF(0, 0) -QPointF(tap->boundingRect().width()/2, -background->boundingRect().height()/20));

    ground->setPos(QPointF(0, 0) -QPointF(ground->boundingRect().width()/2, -background->boundingRect().height()/4));

    ui->graphicsView->setScene(scene);

    scene->addBird();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_startGameclicked(Scene *game_instance)
{
    if(!game_instance->isGameFinished()){
        scene->startGame();
        if (logo->isActive()) {
            delete logo;
        }
        if (tap->isActive()){
            delete tap;
        }
    } else {
        game_instance->prepareNewRound();
    }
}
