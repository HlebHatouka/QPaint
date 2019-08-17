#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include "figure.h"
#include "paintdesk.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_star_Button_clicked();

    void on_rectangle_Button_clicked();

    void on_ellipse_Button_clicked();

    void on_polygon_Button_clicked();

    void on_unite_Button_clicked();

    void on_hand_Button_clicked();

    void on_clean_Button_clicked();

private:
    Ui::MainWindow *ui;
    PaintDesk *paint_desk;
};

#endif // MAINWINDOW_H
