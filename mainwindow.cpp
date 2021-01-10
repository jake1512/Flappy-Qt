#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grounditem.h"
#include "common.h"
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-144, -256, 288, 512);

    pixItem = new QGraphicsPixmapItem(QPixmap(IMG_BACKGROUND_DAY));

    logo = new QGraphicsPixmapItem(QPixmap(IMG_LOGO));
    tap = new QGraphicsPixmapItem(QPixmap(IMG_GAMEINFO));

    scene->addItem(pixItem);
    scene->addItem(logo);
    scene->addItem(tap);

    pixItem->setPos(QPointF(0, 0) -QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));

    logo->setPos(QPointF(0, 0) -QPointF(logo->boundingRect().width()/2, pixItem->boundingRect().height()/8));
    tap->setPos(QPointF(0, 0) -QPointF(tap->boundingRect().width()/2, -pixItem->boundingRect().height()/20));

//    scene->addLine(-700, 0, 700, 0, QPen(Qt::blue));
//    scene->addLine(0, -700, 0, 700, QPen(Qt::blue));

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
