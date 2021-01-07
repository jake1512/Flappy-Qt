#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-144, -256, 288, 512);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(IMG_BACKGROUND_DAY));

    logo = new QGraphicsPixmapItem(QPixmap(IMG_LOGO));
    tap = new QGraphicsPixmapItem(QPixmap(IMG_GAMEINFO));
    ground = new QGraphicsPixmapItem(QPixmap(IMG_GROUND_SEGMENT));
    scene->addItem(pixItem);
    scene->addItem(logo);
    scene->addItem(tap);
    scene->addItem(ground);
    pixItem->setPos(QPointF(0, 0) -QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));

    logo->setPos(QPointF(0, 0) -QPointF(logo->boundingRect().width()/2, pixItem->boundingRect().height()/8));
    tap->setPos(QPointF(0, 0) -QPointF(tap->boundingRect().width()/2, -pixItem->boundingRect().height()/20));
    ground->setPos(QPointF(0, 0) -QPointF(ground->boundingRect().width()/2, -pixItem->boundingRect().height()/4));

    ui->graphicsView->setScene(scene);

    scene->addBird();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startGameBotton_clicked()
{
    scene->startGame();
    if(logo){
        delete  logo;
        logo = nullptr;
    }
    if(tap)
    {
        delete tap;
        tap = nullptr;
    }
}
