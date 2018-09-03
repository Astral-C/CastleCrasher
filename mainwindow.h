#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <castlevaniatile.h>

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
    void updateTile();
    void on_actionOpen_Rom_triggered();

private:
    Ui::MainWindow *ui;
    CastlevaniaMap map;
};

#endif // MAINWINDOW_H
