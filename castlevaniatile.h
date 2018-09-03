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
    uint8_t id;
    CastlevaniaTile();
    CastlevaniaTile(uint8_t type, QString img);
};


class CastlevaniaMap
{
public:
    int mapWidth, mapHeight;
    int scrollX; // the amount to scroll, moving graphics to left

    QGraphicsScene render;

    CastlevaniaTile getTile(int x, int y);
    void setTile(int x, int y, int type);

    void init(int w, int h, int offset, QString areaName, bStream::CFileStream& rom);
    CastlevaniaMap();
};

#endif // CASTLEVANIATILE_H
