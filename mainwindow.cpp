#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&map.render, SIGNAL(selectionChanged()), this, SLOT(updateTile()));
}

void MainWindow::updateTile(){
    if(map.render.selectedItems().length() > 0){
        QPixmap img = QGraphicsPixmapItem(map.render.selectedItems().first()).pixmap();
        ui->tileImg->setPixmap(img);
        ui->tileImg->setGeometry(ui->tileImg->x(), ui->tileImg->y(), img.width(), img.height());
        ui->tileImg->update();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Rom_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Rom", ".");
    bStream::CFileStream file(filename.toStdString(), bStream::Endianess::Little, bStream::OpenMode::In);
    this->map.init(24, 6, 0x1001A, "Entrance", file);
    ui->graphicsView->setMinimumSize(24*32,6*32);
    ui->graphicsView->resize(24*32,6*32);
    this->adjustSize();
    this->ui->graphicsView->setScene(&map.render);
    this->ui->graphicsView->show();
}
