#ifndef CASTLEVANIATILE_H
#define CASTLEVANIATILE_H

#include <QPainter>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <bstream.h>

class CastlevaniaTile : public QGraphicsPixmapItem
{   
private:
    QRectF boundingRect() const override
    {
        //tiles (technically metatiles) are fixed 32x32
        return QRectF(QPoint(0,0), QSize(32, 32));
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        painter->drawPixmap(QPointF(0.0, 0.0), pixmap(), QRectF(0,0,32,32));
        if(isSelected())
        {
            QPen p = painter->pen();
            p.setColor(QColor::fromRgb(255, 105, 180));
            painter->setPen(p);
            painter->drawRect(0,0,31,31);
        }
    }
public:
    int tileType;
    CastlevaniaTile();
    CastlevaniaTile(QString img);
};


class CastlevaniaMap
{
public:
    QString name; //map name
    QString tilePth; //path to tile graphics in Resources
    long mapOffset;
    int mapWidth, mapHeight;

    QGraphicsScene render;

    void init(int w, int h, int offset, QString areaName, bStream::CFileStream& rom);
    void save(bStream::CFileStream& rom);
    void clear();
    void loadGraphics();
    void clearGraphics();
    CastlevaniaMap();
};

#endif // CASTLEVANIATILE_H
