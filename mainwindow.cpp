#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paint_desk = new PaintDesk(this);
    ui->graphicsView->setScene(paint_desk);
    paint_desk->setSceneRect(0,0,500,500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_star_Button_clicked()
{
    paint_desk->setMode(PaintDesk::StarMode);
}

void MainWindow::on_rectangle_Button_clicked()
{
    paint_desk->setMode(PaintDesk::RectangleMode);
}

void MainWindow::on_ellipse_Button_clicked()
{
    paint_desk->setMode(PaintDesk::EllipseMode);
}

void MainWindow::on_polygon_Button_clicked()
{
    paint_desk->setMode(PaintDesk::PolygonMode);
}

void MainWindow::on_unite_Button_clicked()
{
   paint_desk->setMode(PaintDesk::UnitMode);
}

void MainWindow::on_hand_Button_clicked()
{
    paint_desk->setMode(PaintDesk::NoMode);
}
