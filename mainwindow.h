#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsPixmapItem * logo;
    QGraphicsPixmapItem * tap;
    QGraphicsPixmapItem * ground;

private slots:
    void on_startGameBotton_clicked();

private:
    Ui::MainWindow *ui;

    Scene * scene;
};
#endif // MAINWINDOW_H
