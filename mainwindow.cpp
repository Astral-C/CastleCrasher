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
        CastlevaniaTile *tile = qgraphicsitem_cast<CastlevaniaTile*>(map.render.selectedItems().first());
        ui->tileType->setValue(tile->tileType);
        ui->tileImg->setPixmap(tile->pixmap());
        ui->tileImg->setGeometry(ui->tileImg->x(), ui->tileImg->y(), 32, 32);
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
    this->map.init(128, 6, 0x1001A, "Entrance", file); //open first level by default
    ui->graphicsView->setMinimumSize(24*32,6*32);
    ui->graphicsView->resize(24*32,6*32);
    this->adjustSize();
    this->ui->graphicsView->setScene(&map.render);
    this->ui->graphicsView->show();
}

void MainWindow::on_tileType_valueChanged(int arg1)
{
    if(QFile::exists(QString(map.tilePth + QString::number(arg1, 16).toUpper() + ".png")) && map.render.selectedItems().count() > 0){
        QPixmap img = QPixmap(QString(map.tilePth + QString::number(arg1, 16).toUpper() + ".png"));
        CastlevaniaTile *tile = qgraphicsitem_cast<CastlevaniaTile*>(map.render.selectedItems().first());
        ui->tileImg->setPixmap(img);
        tile->setPixmap(img);
        tile->tileType = arg1;
    }
    //todo
    //ui->tileImg->setPixmap(QPixmap());
    //ui->tileImg->setGeometry(ui->tileImg->x(), ui->tileImg->y(), img.width(), img.height());
    //ui->tileImg->update();
}

void MainWindow::on_actionSave_Rom_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Rom", ".");
    bStream::CFileStream file(filename.toStdString(), bStream::Endianess::Little, bStream::OpenMode::Out); //bstream is still broken lol
    this->map.save(file);
}
